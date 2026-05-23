#include "GameOfLife.h"
#include "SelectModePage.h"
#include "Canvas.h"
#include "TemplatePage.h"
#include <QtWidgets/QApplication>
#include <iostream>

// Main entry point of the application
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create the main game window
    GameOfLife w;

    // Initialize mode selection page
    SelectModePage selectGameMode(&(w.getBoard()));
    selectGameMode.show();

    // Initialize the canvas page and the template page
    Canvas canvas(&(w.getBoard()));
    TemplatePage templatePage(&(w.getBoard()));
    

    // Drawing option is selected
    QObject::connect(&selectGameMode, &SelectModePage::openCanvas, [&]() {
        selectGameMode.close();
        canvas.show();
        // handle signal for finishing drawing
        QObject::connect(&canvas, &Canvas::finishDrawing, [&]() {
            w.show();
        });
        // handle signal for backing to the selection page
        QObject::connect(&canvas, &Canvas::backToPrevPage, [&]() {
            canvas.close();
            selectGameMode.show();
        });
    });

    // Template option is selected
    QObject::connect(&selectGameMode, &SelectModePage::openTemplatePage, [&]() {
        selectGameMode.close();
        templatePage.show();
        // handle signal for finishing choosing
        QObject::connect(&templatePage, &TemplatePage::finishGenerating, [&]() {
            w.show();
        });
        // handle signal for backing to the selection page
        QObject::connect(&templatePage, &TemplatePage::backToPrevPage, [&]() {
            templatePage.close();
            selectGameMode.show();
        });
    });

    // File option is selected 
    QObject::connect(&selectGameMode, &SelectModePage::fileChosen, [&]() {
        selectGameMode.close();
        w.show();
    });


    // Handle exiting the application
    QObject::connect(&w, &GameOfLife::exitGame, &QApplication::quit);
    QObject::connect(&w, &GameOfLife::goBackToHomePage, [&]() {
        w.close();
        selectGameMode.show();
    });
    
    // Start the application event loop
    return a.exec();
}
