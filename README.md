// --- BlackFilmDatabase_GUI --- \\

// --- Project Notes / Plan --- \\

The aim of the project is to create a GUI that allows users to search a database of Black films. My motivation for the 
project is simple - there are so many GREAT Black films that I personally haven't watched yet, and so a search 
application to find one to watch would be extremely helpful to myself and others. 

There are a range of tools that I will use - the main one being Qt which is a cross-platform software for creating GUIs. 
The Postgresql database has data on 1000s of Black Films collated from 3 film databases (IMDb, TMDb and OMDb). The 
database uses Postgresql and is therefore queried using Postgresql. To give a high-level overview of the program: 

The main window of the application will have a video playing in the background. The video will be a clip from a popular
Black film. There'll be a 'SEARCH DATABASE' button in the centre of the frame that will navigate to the search page. 
The search page will have two sections, 'Basic Search' and 'Advanced Search'. The basic search will have 5 fields:
1. Title -> A general text field. 
2. Release Year -> A range-based slider. 
3. Genre -> A set of selectable options (boxes).
4. Film Rating -> A set of selectable options (boxes).
5. Language -> A set of selectable options (boxes).

The 'Advanced Search' section will allow the user to narrow their search by offering 6 more fields. These are:
    1. IMDb Rating -> A range-based slider.
    2. Rotten Tomatoes Rating -> A range-based slider.
    3. Keyword -> A general text field.
    4. Actor -> A general text field. 
    5. Director -> A general text field. 
    6. Writer -> A general text field.

Each of the 11 fields will alter the final query sent to the database, and at the bottom of the Search Page there will 
be the 'SEARCH BUTTON' allowing the user to send the query. 

The search results will show on the Results Page. The layout of the page will be simple. Each result will form a row - 
almost like a row of a database but with only a small amount of data. This is so that data on the page doesn't seem 
excessive - the user should be able to quickly identify the main elements when quickly skimming. An alternative idea is 
to show the posters of the films returned in a grid layout. Ultimately, the user will be able to click on one of the
search results and be presented with a page of information on that film alone. The poster will be in the top left-hand
corner and all other information around it. 


