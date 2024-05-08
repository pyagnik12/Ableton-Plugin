# JUCE Plugin Project

Welcome to the **JUCE Plugin Project**! This open-source VST3 plugin is crafted using the JUCE framework, providing a modular and flexible audio processing solution. Our plugin includes two core components:

1. **Compressor**: A versatile audio compressor with adjustable parameters to help you shape your sound.
2. **Marauder**: A unique distortion effect with modular features that allow you to change the bit depth, drive levels, and add white noise for sonic variety.

## Features

- **Compressor**: Fine-tune your dynamics with threshold, ratio, attack, and release controls.
- **Marauder (Distortion)**:
  - Adjust bit depth to achieve different tonal qualities.
  - Control drive to introduce distortion at varying intensities.
  - Add white noise for additional textural layering.
- **VST3 Plugin**: Compatible with most major DAWs.
- **Open Source**: Modify and improve this plugin as per your creative needs.

## Installation

1. **Clone Repository**:
    ```bash
    git clone <repo_url>
    ```
2. **JUCE Framework**: Ensure you have JUCE set up by following the [official instructions](https://juce.com/get-juce).
3. **Build the Project**:
    - Open the `.jucer` project file in the Projucer.
    - Configure your desired export target.
    - Save and open the project in your preferred IDE (e.g., Visual Studio, Xcode).
    - Build the project within your IDE.

4. **Install the Plugin**:
    - Locate the built VST3 file in the build directory.
    - Copy or link this file to your DAW's VST3 directory.

## Usage

1. **Add the Plugin**: Load the plugin in your DAW as you would with any other VST3 plugin.
2. **Adjust the Compressor**: Set your preferred threshold, ratio, attack, and release values to control dynamics.
3. **Dial in the Marauder**: Change bit depth, drive intensity, and add noise to taste.
4. **Experiment**: This plugin is modular, so mix and match the effects for unique sonic combinations!

## Contribution Guidelines

We welcome contributions from the community! Please follow these steps if you'd like to contribute:

1. **Fork** the repository.
2. **Create a Branch**:
    ```bash
    git checkout -b feature/YourFeature
    ```
3. **Commit Changes**: Ensure your changes are thoroughly tested.
4. **Push Branch**:
    ```bash
    git push origin feature/YourFeature
    ```
5. **Open a Pull Request**: Provide a detailed description of your changes.

## License

This plugin is created with the free versioin of Juce, allowing it to be open source.

## Contact

For questions, issues, or suggestions, feel free to open an issue on GitHub or contact the development team directly.

Happy music-making! 
