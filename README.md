# CryptoSW-App2

CryptoSW-App2 is a desktop application built with C++ and the Qt framework that provides a user-friendly interface for performing various cryptographic operations. It leverages the powerful Crypto++ library to offer a range of functionalities, including RSA and DSA operations.

## Features

*   **RSA Key Pair Generation:** Generate RSA public and private key pairs.
*   **RSA Encryption:** Encrypt files using an RSA public key.
*   **RSA Decryption:** Decrypt files using an RSA private key.
*   **DSA Signature Generation:** Generate a digital signature for a file using a DSA private key.
*   **DSA Signature Verification:** Verify the digital signature of a file using a DSA public key.

## GUI

The application provides a simple and intuitive graphical user interface with the following key components:

*   **Operation Dropdown**: A combo box that allows you to select the desired cryptographic operation (e.g., RSA Key-Pair Generation, RSA Encryption, DSA Sign).
*   **Input Text Field**: A multi-line text area where you can directly type or paste plaintext for operations like encryption or signing.
*   **Input File Path Display**: A read-only field that shows the path of the file selected via the "Upload" button.
*   **Upload Button**: Opens a file dialog to select an input file for operations that require file-based input (e.g., encrypting a file, decrypting a ciphertext, or providing a signature for verification).
*   **Process Button**: Executes the currently selected cryptographic operation using the provided input (text or file).
*   **Download Button**: Becomes active after an operation that produces an output (like encryption, decryption, or signing). Clicking it opens a save file dialog to save the generated output (e.g., ciphertext, decrypted data, or signature) to your local system.
*   **Status Log**: A text area that displays real-time progress, success messages, and any errors encountered during operations.
*   **Progress Bar**: (Optional) A visual indicator that shows the progress of longer operations, though most cryptographic operations are very fast.

## Project Structure

```
.
├── CMakeLists.txt
├── config
│   └── config.json
├── cryptopp
│   ├── include
│   └── libcryptopp.a
├── main.cpp
└── src
    ├── crypto
    │   ├── CryptoManager.cpp
    │   └── CryptoManager.h
    ├── gui
    │   ├── MainWindow.cpp
    │   ├── MainWindow.h
    │   └── mainwindow.ui
    └── utils
        ├── file_utils.cpp
        ├── file_utils.h
        ├── KeyUtils.cpp
        └── KeyUtils.h
```

### Key Components

*   **`main.cpp`**: The main entry point of the application.
*   **`src/gui/`**: Contains the Qt-based graphical user interface code.
    *   `MainWindow.h`, `MainWindow.cpp`, and `mainwindow.ui` define the main window of the application.
*   **`src/crypto/`**: Implements the core cryptographic functionalities.
    *   `CryptoManager.h` and `CryptoManager.cpp` wrap the Crypto++ library to provide a simplified interface for cryptographic operations.
*   **`src/utils/`**: Provides helper functions for file operations and key management.
*   **`cryptopp/`**: Contains the pre-compiled Crypto++ library and its header files.
*   **`config/config.json`**: Configuration file for the application.
*   **`CMakeLists.txt`**: The build script for the project.

## Building the Project

The project is built using CMake. You will need to have CMake and a C++ compiler installed on your system. You will also need to have the Qt6 development libraries installed.

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    ```
2.  **Create a build directory:**
    ```bash
    mkdir build && cd build
    ```
3.  **Run CMake:**
    ```bash
    cmake ..
    ```
4.  **Build the project:**
    ```bash
    cmake --build .
    ```

## Usage

Once the project is built, you can run the executable from the build directory. The application will launch a graphical user interface that allows you to select a cryptographic operation, choose a file, and perform the operation.

## Configuration

The application can be configured through the `config/config.json` file. The following options are available:

*   `dsa_key_size`: The size of the DSA keys to be generated.
*   `hash_algorithm`: The default hash algorithm to be used.
*   `keys_dir`: The directory where the generated keys will be stored.
*   `output_dir`: The directory where the output files will be stored.
*   `rsa_key_size`: The size of the RSA keys to be generated.
*   `rsa_padding`: The padding scheme to be used for RSA encryption.

## Dependencies

*   **Qt6:** A cross-platform application development framework.
*   **Crypto++:** A free C++ class library of cryptographic schemes.
