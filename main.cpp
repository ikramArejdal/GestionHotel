<<<<<<< Updated upstream
#include "gestiondehotel.h"

#include <QApplication>

=======
#include <QApplication>

// On inclut la fenêtre de login. 
// Grâce à votre CMakeLists.txt (include_directories), 
// vous pouvez utiliser "views/LoginWindow.h" ou juste "LoginWindow.h".
#include "views/LoginWindow.h" 

>>>>>>> Stashed changes
int main(int argc, char *argv[])
{
    // 1. Initialisation de l'application Qt
    QApplication a(argc, argv);

    // (Optionnel) Méta-données de l'application
    a.setApplicationName("Gestion Hotel");
    a.setApplicationVersion("1.0");

    // 2. Création de la fenêtre de connexion
    LoginWindow w;
    
    // 3. Affichage de la fenêtre
    w.show();
<<<<<<< Updated upstream
=======

    // 4. Lancement de la boucle d'événements (le programme tourne en boucle)
>>>>>>> Stashed changes
    return a.exec();
}