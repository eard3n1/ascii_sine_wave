import subprocess
from math import sin
from config import *

def generate_frame(phase: int):
    frame = [[" "]*WIDTH for _ in range(HEIGHT)]
    char_count = len(CHARS) - 1

    for x in range(WIDTH):
        y = int(AMPLITUDE * sin(FREQUENCY * (x + phase)) + OFFSET)
        
        if 0 <= y < HEIGHT:
            frac = (y - (OFFSET - AMPLITUDE)) / (2 * AMPLITUDE)
            char_index = max(0, min(char_count, int(frac * char_count)))
            frame[y][x] = CHARS[char_index]

    return "\n".join("".join(row) for row in frame) + "\n---\n"

def main():
    proc = subprocess.Popen(["./render.exe"], stdin=subprocess.PIPE, text=True)
    phase = 0
    try:
        while True:
            frame_str = generate_frame(phase)
            proc.stdin.write(frame_str)
            proc.stdin.flush()
            phase += 1

    except KeyboardInterrupt:
        proc.stdin.close()
        proc.terminate()

if __name__ == "__main__":
    main()