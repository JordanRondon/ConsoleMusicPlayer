#include <iostream>
#include "MusicPlayer.h"

using namespace std;

int main() {
    
    //MusicPlayer player;

    //player.load("C:/Users/JORDAN/Music/asd.mp3");
    //player.play();

    //// Espera por la entrada del usuario para detener la música
    //std::cin.get();

    try {
        MusicPlayer player;

        // Ruta del archivo MP3
        const char* filePath = "C:/Users/JORDAN/Music/asd.mp3";

        player.load(filePath);
        player.play();

        // Espera por la entrada del usuario para controlar la música
        char input;
        while (true) {
            std::cout << "Comandos: (f) Adelantar 5s, (b) Retroceder 5s, (q) Detener\n";
            std::cin >> input;

            if (input == 'f') {
                player.seekForward(); // Adelantar 5 segundos
            }
            else if (input == 'b') {
                player.seekBackward(); // Retroceder 5 segundos
            }
            else if (input == 'q') {
                player.stop(); // Detener la reproducción
                break;
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}