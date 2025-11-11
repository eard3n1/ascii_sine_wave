import subprocess
import math
from config import *

def generate_frame(phase: int):
    frame = [[" "]*WIDTH for _ in range(HEIGHT)]
    char_count = len(CHARS) - 1
    two_amplitude = 2 * AMPLITUDE

    for x in range(WIDTH):
        y_float = AMPLITUDE * math.sin(FREQUENCY * (x + phase)) + OFFSET
        y = int(math.floor(y_float))
        
        if 0 <= y < HEIGHT:
            frac = (y_float - (OFFSET - AMPLITUDE)) / two_amplitude
            char_index = int(frac * char_count)
            char_index = max(0, min(char_count, char_index))
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
