# Building and Running the Light Monitoring Program

---

## Prerequisites:
Before proceeding, ensure you have the following installed on your system:
- **Mingw**: This is a minimal GNU for Windows development environment. You'll need it for compiling C++ code.
- **Make**: This is a build automation tool. It simplifies the process of compiling and building your code.

## Instructions:
1. **Set Up Your Environment**:
   - Make sure you have Mingw installed on your system. If not, you can download and install it from the [official website](https://www.mingw-w64.org/).
   - Similarly, ensure you have Make installed. You can typically install it via your package manager or by downloading it from its [official website](https://www.gnu.org/software/make/).

2. **What You'll Need**:
   - Download the code folder onto your local machine.
   - Before you start, make sure you have these files in your project folder:
     1. `main.cpp`
     2. `httplib.h`
     3. `json.hpp`

## Key Components:
1. **Light Structure**:
   - This represents each light in the system and stores information like its ID, name, room, brightness, and whether it's on or off.
2. **getLightDetails Function**:
   - This function gets details about a specific light by making an HTTP request to the home automation system.
3. **getInitialLightsState Function**:
   - This function retrieves the initial state of all lights from the system and stores them in a map.
4. **monitorLightChanges Function**:
   - Continuously monitors changes in the state of lights and outputs any changes detected.

## Run the Light Server:
Before running the program, ensure that the light server of your system is up and running. The program expects it to be accessible at `http://localhost:8080`.

## Compile and Build the Program:
1. Open a terminal and navigate to the directory containing the code.
2. Follow the instructions provided in your `Build_Instructions.txt` in the Challenge folder to compile and build the program using Mingw and Make.

## Run the Executable:
After successfully building the program, run the generated executable. This will start monitoring the lights in your home automation system and try making the changes in the browser by going to `http://localhost:8080` and observe the changes in the terminal.

## Additional Notes:
- The program continuously monitors changes in the state of lights and reports them in JSON format.
- Make sure to have the light server running before executing the program.
- If you encounter any issues during the build process or while running the program, refer to the documentation or seek assistance.
