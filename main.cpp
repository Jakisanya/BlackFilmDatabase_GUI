// --- BlackFilmDatabase_GUI --- \\

// --- Project Notes / Plan --- \\

//  I need to identify all the base components that I need to make this work. By base components I mean the
//  libraries - and by extension - specific classes and functions.

//  I want a program/executable that opens a window. The first page has a video playing in the background. Or
//  maybe even a reel of short video clips from a range of Black films. In the foreground is a button that takes
//  me to the second page - the search page. The second page has no video graphics, it's just a form that allows
//  me to perform a parameter/filed-based database search. I'll need to decide on the parameters that will be
//  available. This means that I need to find a library that can display a form.

//  I need to connect my database to the backend - this should be as simple as providing a connection string and
//  database name.

//  I still need a third page that shows the results of the search. The idea is not to aim for anything too
//  spectacular at first; a list of results with the main data either in line or just below it. Maybe as an
//  eventual improvement I could make the films in the list clickable, which will create a new window displaying
//  a single film - the poster to the film in the top left and more detailed information around it.

//  GUI Framework/Library: Qt (supports GUI development to create windows, buttons, forms, etc.)
//  Video Playback: FFmpeg (for decoding and playing videos) / SDL (provides multimedia functionalities)
//  Database Connectivity: PostgreSQL C++ Library (libpqxx)
//  Database Query Execution: libpqxx
//  GUI Form Components: Qt (text fields, buttons, labels, etc.)
//  UI Navigation: Qt (mechanisms to switch between different pages/screens)
//  Displaying Search Results: Qt (dynamically populating GUI elements - like a list - with search results)
//  Handling User Interactions: Qt , C++ Standard User Input/Event Handling structures

// 2. A higher level understanding of how I should structure the project:

#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QtMultimedia>

class VideoWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    VideoWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent), timer(this) {
        setFixedSize(640, 480); // Set the size of the window

        // Initialize FFmpeg
        av_register_all();
        avcodec_register_all();
        avformat_network_init();

        // Initialize timer to update frames
        connect(&timer, &QTimer::timeout, this, &VideoWidget::updateFrame);
        timer.start(40); // Update every 40ms (25 frames per second)
    }

    ~VideoWidget() {
        closeVideo();
    }

protected:
    void initializeGL() override {
        initializeOpenGLFunctions();
    }

    void paintGL() override {
        if (videoStreamIndex == -1 || !frame)
            return;

        glClear(GL_COLOR_BUFFER_BIT);

        // Convert frame to OpenGL texture
        QImage image(frame->data[0], frame->width, frame->height, QImage::Format_RGB888);
        texture = QOpenGLTexture(image.mirrored()); // Mirror image
        texture.bind();

        // sws_scale(swsContext, data, linesize, 0, codecContext->height, frameRGB->data, frameRGB->linesize);

        // Draw texture
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
        glEnd();
    }

    void updateFrame() {
        if (!openVideo())
            return;

        AVPacket packet;
        while (av_read_frame(formatContext, &packet) >= 0) {
            if (packet.stream_index == videoStreamIndex) {
                avcodec_send_packet(codecContext, &packet);
                if (avcodec_receive_frame(codecContext, frame) == 0) {
                    update();
                    av_packet_unref(&packet);
                    break;
                }
            }
            av_packet_unref(&packet);
        }
    }

    bool openVideo() {
        if (!formatContext) {
            // Open video file
            if (avformat_open_input(&formatContext, "path_to_video_file.mp4", nullptr, nullptr) != 0) {
                qWarning() << "Error opening video file";
                return false;
            }

            // Find video stream information and fill the AVFormatContext structure
            if (avformat_find_stream_info(formatContext, nullptr) < 0) {
                qWarning() << "Error finding stream information";
                return false;
            }

            // Find video stream index
            for (int i = 0; i < formatContext->nb_streams; i++) {
                if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                    videoStreamIndex = i;
                    break;
                }
            }

            if (videoStreamIndex == -1) {
                qWarning() << "Error finding video stream";
                return false;
            }

            // Get video codec parameters
            AVCodec *codec = avcodec_find_decoder(formatContext->streams[videoStreamIndex]->codecpar->codec_id);
            if (!codec) {
                qWarning() << "Error finding video decoder";
                return false;
            }

            // Allocate video codec context
            codecContext = avcodec_alloc_context3(codec);
            if (!codecContext) {
                qWarning() << "Error allocating video codec context";
                return false;
            }

            // Open video codec
            if (avcodec_open2(codecContext, codec, nullptr) < 0) {
                qWarning() << "Error opening video codec";
                return false;
            }

            // Allocate frame
            frame = av_frame_alloc();
            if (!frame) {
                qWarning() << "Error allocating video frame";
                return false;
            }

            // Create the Software Scaler (sws) Context. It's a data structure used for image scaling and format conversion.
            swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width,
                                        codecContext->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, nullptr, nullptr, nullptr);
            if (!swsContext) {
                qDebug() << "Error creating sws context";
                return false;
            }

            timer.setInterval(40); // 25 frames per second
            connect(&timer, &QTimer::timeout, this, &VideoWidget::updateFrame);
            timer.start();
            return true;
        }
        return true;
    }

    void resizeGL(int w, int h) override {
        glViewport(0, 0, w, h);
    }

    void closeVideo() {
        if (formatContext) {
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            av_frame_free(&frame);
            formatContext = nullptr;
            codecContext = nullptr;
            frame = nullptr;
            videoStreamIndex = -1;
        }
    }

private:
    // Create a video format context (contains data about video format)
    AVFormatContext* formatContext = nullptr;
    AVCodecContext* codecContext = nullptr;
    AVFrame* frame = nullptr;
    struct SwsContext *swsContext;
    QTimer timer;
    int videoStreamIndex = -1;
    QOpenGLTexture texture;
};

class VideoWindow : public QMainWindow {
public:
    VideoWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        resize(800, 600);
        setWindowTitle("Black Film Database Search Tool");

        // The video has to be inside a widget/label
        QWidget* centralWidget;
        mainWindow->setCentralWidget(centralWidget);

        // Create layout for the central widget
        // QVBoxLayout manages the layout of the widgets inside the central widget.
        QVBoxLayout vBoxLayout(centralWidget);

        // Create video widget
        QLabel videoLabel;
        videoLabel.setAlignment(Qt::AlignCenter);

        // Create button
        QPushButton searchButton = QPushButton("Search Database");
        connect(searchButton, &QPushButton::clicked, &searchDatabase);
        vBoxLayout.addWidget(&searchButton);

        // Load video
        QString filmClipPath = "";
        if (!videoWidget->loadVideo(filmClipPath))
            qDebug() << "Failed to load video";

        // The video label widget holding the video is placed within the layout of the central widget
        vBoxLayout.addWidget(&videoLabel);

        // Create central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Create layout for central widget
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Create video widget
        VideoWidget videoWidget;

        layout->addWidget(&videoWidget);

        // Create button
        QPushButton *searchButton = new QPushButton("Search Database", this);
        connect(searchButton, &QPushButton::clicked, this, &VideoWindow::searchDatabase);
        layout->addWidget(searchButton);

        // Set layout
        centralWidget->setLayout(layout);
    }

private slots:
    void searchDatabase() {
        // Implement your database search functionality here
        QMessageBox::information(this, "Database Search", "Performing search...");
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VideoWidget widget;
    widget.show();

    return app.exec();
}
