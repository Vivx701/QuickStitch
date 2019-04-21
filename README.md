# QuickStitch
Simple image stitching program written in Qt5 C++.
Provides functionalites to stitch images horizonally and vertically.


## Getting Started
Download the releases or clone the repo. Build and install the app in local machine.
After installation you can see QuickStitch  on your Application list.
See building and installation section more details.


### Building and installation of source code

1. Install build dependencies
     
    Debian-based
    -------------

    * g++ >= 5
    * libx11-dev and libxext-dev
    * qtbase5-dev and libqt5x11extras5-dev
    * libqt5svg5-dev 
    * qttools5-dev-tools

    Red Hat based
    --------------
    * gcc-c++
    * libX11-devel
    * libXext-devel
    * qt5-qtx11extras-devel
    * qt5-qtbase-devel
    * qt5-qtsvg-devel
    * qt5-qttools-devel

    Arch based
    ------------
    * gcc 
    * libx11 and libxext
    * qt5-base and qt5-x11extras
    * qt5-svg 
    * qt5-tools

    OpenSUSE based
    ---------------
    * gcc-c++
    * libX11-devel
    * libXext-devel
    * libqt5-qtx11extras-devel
    * libqt5-qtbase-devel
    * libqt5-qtsvg-devel
    * libqt5-qttools-devel

2. Building and installation
    
    ```
    qmake  <PATH of QuickStitch.pro>
    make 
    sudo make install
    ```

3. Uninstalling

    ```
    sudo make uninstall
    ``` 

## Authors
* **Vivek.P**  - (https://github.com/Vivx701)


## License
This project is licensed under the GPLV3 License - see the [LICENSE](LICENSE) file for details

## Screenshots
![appwindow](screenshots/quickstitch.png?raw=true)
![savescreen](screenshots/savescreen.png?raw=true)