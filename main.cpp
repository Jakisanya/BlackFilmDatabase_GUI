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


#include <iostream>

int main() {

    return 0;
}

