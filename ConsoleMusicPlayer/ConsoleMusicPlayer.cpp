#include <iostream>
//#include "bass.h"

using namespace std;

int main() {
    // Inicializar BASS
    //if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
    //    std::cerr << "Error al inicializar BASS: " << BASS_ErrorGetCode() << std::endl;
    //    return 1;
    //}

    //// Cargar un archivo MP3
    //const char* filePath = "C:\\Users\\JORDAN\\Music\\asd.mp3";
    //HSTREAM stream = BASS_StreamCreateFile(FALSE, filePath, 0, 0, 0);
    //if (!stream) {
    //    std::cerr << "Error al cargar el archivo MP3: " << BASS_ErrorGetCode() << std::endl;
    //    BASS_Free();
    //    return 1;
    //}

    //// Reproducir el archivo
    //if (!BASS_ChannelPlay(stream, FALSE)) {
    //    std::cerr << "Error al reproducir el archivo: " << BASS_ErrorGetCode() << std::endl;
    //    BASS_StreamFree(stream);
    //    BASS_Free();
    //    return 1;
    //}

    //std::cout << "Reproduciendo música. Presiona Enter para detener..." << std::endl;
    //std::cin.get();

    //QWORD length = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    //double duration = BASS_ChannelBytes2Seconds(stream, length);
    //std::cout << "Duración: " << duration << " segundos" << std::endl;

    //// Liberar recursos
    //BASS_StreamFree(stream);
    //BASS_Free();

    return 0;
}