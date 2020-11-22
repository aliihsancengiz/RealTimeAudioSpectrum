cmake_minimum_required(VERSION 3.5)

project(SpectrumAnalyzer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)


if(ANDROID)
  add_library(SpectrumAnalyzer SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(SpectrumAnalyzer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    spectrum.cpp
    spectrum.h
    WavReader/AudioFile.h
    audiodata.cpp
    audiodata.h
    fft/Array.h
    fft/Array.hpp
    fft/def.h
    fft/DynArray.h
    fft/DynArray.hpp
    fft/FFTReal.h
    fft/FFTReal.hpp
    fft/FFTRealFixLen.h
    fft/FFTRealFixLen.hpp
    fft/FFTRealPassDirect.h
    fft/FFTRealPassDirect.hpp
    fft/FFTRealPassInverse.h
    fft/FFTRealPassInverse.hpp
    fft/FFTRealSelect.h
    fft/FFTRealSelect.hpp
    fft/FFTRealUseTrigo.h
    fft/FFTRealUseTrigo.hpp
    fft/OscSinCos.h
    fft/OscSinCos.hpp
    FFTObj.h
  )
endif()

target_link_libraries(SpectrumAnalyzer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
