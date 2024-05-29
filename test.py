import os
import time

# Path to the named pipe
pipe_path = "/tmp/mousepipe"

# Function to send commands to the named pipe
def send_command(command):
    try:
        with open(pipe_path, "w") as pipe:
            pipe.write(command)
        print(f"Sent command: {command}")
    except Exception as e:
        print(f"Error sending command: {e}")

# Example usage
if __name__ == "__main__":
    # Send commands in a loop
    while True:
        command = input("Enter command (w, s, a, d, space, c) or 'q' to quit: ")
        if command == "q":
            break
        elif command in ['w', 's', 'a', 'd', ' ', 'c']:
            send_command(command)
        else:
            print("Invalid command. Please enter one of: w, s, a, d, space, c")
        time.sleep(0.1)  # Add a small delay to avoid flooding the pipe