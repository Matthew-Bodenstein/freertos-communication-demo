# FreeRTOS Communication Demo

This project demonstrates a **multi-tasking embedded communication system** using the **FreeRTOS Windows Simulator**.  
It simulates real-time tasks for communication, sensor data collection, and error handling, showing how FreeRTOS handles  
**queues, semaphores, and task scheduling** in an embedded environment.

---

##  Features
- **Task A (Communication):** Sends simulated UART heartbeat messages.  
- **Task B (Sensor):** Generates random sensor values and sends them via a queue.  
- **Task C (Error Handling):** Reads sensor values, flags errors if out of range.  
- Uses **queues** for inter-task communication.  
- Uses **semaphores** for resource protection.  
- Includes **timestamped logging** for each task action.  

---

## File Structure
```
freertos-communication-demo/
src/
main.cpp            # Application code
FreeRTOSConfig.h    # RTOS configuration
screenshots/
console_output.png  # Example runtime output
README.md
.gitignore
```

---

## Example Output
```
[1000 ticks | 1.00 s][Task A] Sending heartbeat...
[1000 ticks | 1.00 s][Task B] Sensor value = 63
[2000 ticks | 2.00 s][Task B] Sensor value = 94
[2000 ticks | 2.00 s][Task C] Sensor value out of range! Error flagged: 94
[3000 ticks | 3.00 s][Task A] Sending heartbeat...
```

---

##  How to Build & Run
This project is designed to run on top of the **FreeRTOS Windows Simulator**.  
If you download this repo by itself, it will not compile straight away — you also need the FreeRTOS kernel sources and headers.

### Steps:
1. Install **Visual Studio (Community Edition)**.  
2. Download the **FreeRTOS Windows Simulator** from [FreeRTOS.org](https://www.freertos.org/porting-a-freertos-demo-to-windows.html).  
3. Open the Visual Studio solution that comes with the simulator.  
4. Add the files from this repo’s `src/` folder (`main.cpp` and `FreeRTOSConfig.h`) into the project.  
5. Build and run in Debug mode.  
6. The console will display timestamped logs (see screenshot).  

---

##  Why Isn’t the Full FreeRTOS Included?
FreeRTOS is a full real-time operating system with many source files and ports.  
Including the entire kernel here would make the repository unnecessarily large and messy.  

Instead:  
- This repo contains **only the custom demo code and config** that I wrote.  
- The README explains how to run it with FreeRTOS.  
- Engineers familiar with embedded systems will already have FreeRTOS or know how to get it.  

This keeps the repo clean and professional, while still being reproducible.

---

##  Why This Project?
This demo highlights:  
- **Embedded communication software** principles.  
- **Real-time task scheduling** using FreeRTOS.  
- **Inter-task communication** with queues/semaphores.  
- How to adapt embedded software for different hardware environments.

It mirrors real-world engineering tasks such as:  
- Developing software for SoC-based systems.  
- Integrating communication modules into third-party equipment.  
- Following coding standards in multi-threaded environments.

---

## License
This project uses FreeRTOS under its open-source license. See [FreeRTOS License](https://www.freertos.org/license.html).
