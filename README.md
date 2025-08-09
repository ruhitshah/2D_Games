# ✈️ Airplane Battle Game (EasyX C++)

A simple 2D airplane game built with **EasyX** graphics library in C++.  
The player controls an airplane to dodge enemy planes while scoring points and surviving as long as possible.

---

## 📌 Features
- **Player Movement**: Move up, down, left, and right using arrow keys.
- **Enemies**: Enemy planes spawn from the top and move down.
- **Difficulty Scaling**: Enemy speed and spawn rate increase with score.
- **Lives System**: Player starts with 3 lives.
- **Pause & Resume**: Press `ESC` to pause/resume.
- **Restart Option**: Restart the game after game over.
- **Start & Game Over Screens** with score display.

---

## 🎮 Controls
| Key        | Action                              |
|------------|-------------------------------------|
| `↑`        | Move Up                             |
| `↓`        | Move Down                           |
| `←`        | Move Left                           |
| `→`        | Move Right                          |
| `ESC`      | Pause / Resume / Exit               |
| `Enter`    | Start Game / Restart after Game Over|

---

## 🖼 Screens
### Start Screen
- Displays game title, instructions, and controls.

### Gameplay
- Player airplane at the bottom.
- Enemy planes falling from the top.
- Score and lives displayed on the top of the screen.

### Game Over Screen
- Shows final score.
- Option to restart or exit.

---

## 🛠 Requirements
- **Compiler**: MinGW (for Code::Blocks) or MSVC (Visual Studio)
- **EasyX Graphics Library** for Windows  
  [Download EasyX](https://easyx.cn/)
- **Windows OS** (EasyX is Windows-only)

---

## 📂 Project Structure
├── main.cpp # Main game source code
├── README.md # Project documentation

---

## 🚀 How to Build & Run
1. **Install EasyX**
   - Download and install from [EasyX Official Website](https://easyx.cn/).
   - Configure EasyX in your compiler (include and library paths).

2. **Open Project**
   - Open `main.cpp` in Code::Blocks or Visual Studio.

3. **Compile**
   - Make sure to link EasyX library:
     - In Code::Blocks:  
       Add `easyx.a` or `graphics.lib` in **Project → Build Options → Linker settings**.
     - In Visual Studio:  
       Add `graphics.lib` in **Project Properties → Linker → Input → Additional Dependencies**.

4. **Run**
   - Press **Run** or execute the compiled `.exe`.

---

## 📜 License
This project is open-source. You can modify and use it freely for learning purposes.

---

## ✏️ Author
Developed by **Ruhit Shah**  
A fun project to learn EasyX graphics and C++ game programming.

---
