#!/bin/bash

# Prompt the user for the port number
read -p "Enter the port number to close sockets on: " port

# Find all sockets on the specified port and extract PIDs
pids=$(sudo lsof -i :"${port}" | awk 'NR>1 {print $2}')

# Check if any processes are using the specified port
if [ -z "$pids" ]; then
  echo "No processes found using port ${port}."
  exit 1
fi

# Terminate processes using the extracted PIDs
echo "Terminating processes using port ${port}:"
for pid in $pids; do
  sudo kill -9 "$pid"
  echo "Terminated process with PID: $pid"
done

echo "All processes using port ${port} have been terminated."

