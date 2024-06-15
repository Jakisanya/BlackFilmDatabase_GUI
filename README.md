// --- BlackFilmDatabase_GUI --- \\\

// --- Project Notes / Plan --- \\\

The aim of the project is to create a GUI that allows users to search a database of Black films. My motivation for the 
project is simple - there are so many GREAT Black films that I personally haven't watched yet, and so a search 
application to find one to watch would be extremely helpful to myself and others. 

There are a range of tools that I will use - the main one being Qt which is a cross-platform software for creating GUIs. 
The Postgresql database has data on 1000s of Black Films collated from 3 film databases (IMDb, TMDb and OMDb). The 
database uses Postgresql and is therefore queried using Postgresql. To give a high-level overview of the program: 

The landing page of the application will have a video playing in the background. The video will be a clip from a popular
Black film. X-Men: Apocalypse is shown in the Figma export below but it is not a Black film - just an example used in 
the design. It is in the unfiltered database because of the Black actors who acted in it; 1% of its Supporting Actors 
are Black. I intend to either provide functionality to set a Black_Lead_Proportion / Black_Support_Proportion / 
Black_Cast_Proportion threshold so that the search is filtered more accurately. As of now, the user can sort the results 
by these fields. I kind of like the idea that every film a Black person has acted in is in the database - this will most 
likely prove useful as I develop the project. There'll be an 'ENTER' button in the centre of the frame that will 
navigate to the search page.

![Landing Page](https://github.com/Jakisanya/BlackFilmDatabase_GUI/blob/main/Black%20Film%20Database%20Search%20_%20Landing%20Page.png)

The search page will have two sections, 'Basic Search' and 'Advanced Search' (to be added). The basic search will have 7 fields:
1. Title -> A general text field. 
2. Release Year -> Two value input fields ('From' and 'To'). 
3. Genre -> A set of selectable options (boxes).
4. Film Rating -> A set of selectable options (boxes).
5. Language -> A set of selectable options (boxes).
6. IMDb Rating -> A value input field.
7. Rotten Tomatoes Rating -> A value input field.

The 'Advanced Search' section will allow the user to narrow their search by offering 4 more fields. These are:
1. Keyword -> A general text field.
2. Actor -> A general text field. 
3. Director -> A general text field. 
4. Writer -> A general text field.

Each of the 11 fields will alter the final query sent to the database, and at the bottom of the Search Page there will 
be the 'SEARCH BUTTON' allowing the user to send the query. 

<div align="center">
  <img src="https://github.com/Jakisanya/BlackFilmDatabase_GUI/blob/main/Black%20Film%20Database%20Search%20_%20Search%20Page.png" alt="Figma Prototype Design: Search Page">
</div>

![Search Page]()

The search results will show on the Results Page. The layout of the page will be simple. Each result will form a row of 
data pertaining to a film. The data will be retrieved directly from the database - but with a select number of columns. 
This is so that data on the page doesn't seem excessive - the user should be able to quickly identify the 
main elements when skimming. The user will be able to sort the list of results by any of the fields (lexicographically 
/ numerically). 

The fields (excluding the 7 basic search fields) are:
8. Black Lead Actor Proportion (the number of Black actors among the film's lead actors as a proportion)
9. Black Supporting Actor Proportion (the number of Black actors among the film's supporting actors as a proportion)
10. Black_cast_proportion (the number of Black actors in the film's entire cast as a proportion)
11. Budget 
12. Opening Weekend Gross 
13. Worldwide Gross 
14. Total Awards amongst the Lead Actors 
15. Total Awards amongst the Supporting Actors 
16. Total Awards amongst the Movie Cast 
17. Total Awards amongst the Writers 
18. Total Awards amongst the Directors 
19. Total Awards amongst the Soundtrack Credits 

![Results Page](https://github.com/Jakisanya/BlackFilmDatabase_GUI/blob/main/Black%20Film%20Database%20Search%20_%20Results%20Page.png)

Ultimately, the user will be able to click on one of the search results and be presented with a page of information on 
that film alone (film highlight page). The poster will be on the left, plot in the top-right and a table with all other 
information about the film below it.

![Film Highlight Page](https://github.com/Jakisanya/BlackFilmDatabase_GUI/blob/main/Black%20Film%20Database%20Search%20_%20Film%20Highlight%20Page.png)
