## Klopotenko's Cookbook

**Klopotenko's Cookbook** is a cross-platform client-server application built using **C++**, **Qt**, **MySQL** and **QML** for the GUI, compatible with **macOS**, **Windows**, **Linux**, and **Android**.

### Key Features:

- **Recipe Browsing**: Users can view all recipes via a dropdown menu, add new recipes, or view their favorites.

- **Search**: A search bar allows users to find specific recipes by name.

- **Filters**: Filter recipes by:
  - Dish category (e.g., first course, dessert)
  - National cuisine
  - Keywords (e.g., soup, salad)
  - Ingredients

- **Favorites**: Easily mark recipes as favorites by clicking the "heart" icon on the main page.

- **Detailed Recipe View**: Clicking on a recipe opens a detailed page with:
  - Cooking instructions
  - Meal’s output in grams, calories, and number of servings
  - Ability to recalculate these values based on a custom number of servings.

- **Edit and Delete**: Each recipe page includes options to edit or delete the recipe.

This app provides an intuitive and user-friendly way to manage, search, and customize recipes.

## Project File Structure

/Cookbook

│   ├── main.cpp                  # Main file to launch the application

├── /client                       # Code for the client-side

│   ├── /src                      # Client source files
│   │   ├── client.cpp            # Logic for client operations
│   │   ├── network_client.cpp     # Logic for server interaction
│   │   ├── json_parser.cpp       # Logic for JSON handling
│   │   └── qml_handler.cpp       # Logic for QML integration

│   └── /include                  # Client header files
│       ├── client.h              # Header file for the client
│       ├── network_client.h       # Header file for network functions
│       ├── json_parser.h         # Header file for the JSON parser
│       └── qml_handler.h         # Header file for QML handling

│
├── /server                       # Code for the server-side
│   ├── /src                      # Server source files
│   │   ├── server.cpp            # Main server logic
│   │   ├── request_handler.cpp    # Logic for handling client requests
│   │   ├── database_handler.cpp    # Logic for database operations

│   └── /include                  # Server header files
│       ├── server.h              # Header file for the server
│       ├── request_handler.h      # Header file for request handling
│       └── database_handler.h      # Header file for database operations

