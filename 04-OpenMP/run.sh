#!/bin/bash

# Path to the executable
EXECUTABLE="./a"

# Check if the executable exists
if [[ ! -f "$EXECUTABLE" ]]; then
    echo "Error: Executable '$EXECUTABLE' not found!"
    exit 1
fi

# File to store the results
OUTPUT_FILE="run_times.txt"
echo "Thread Count | Execution Time (s)" > $OUTPUT_FILE
echo "---------------------------------" >> $OUTPUT_FILE

# Loop through thread counts from 1 to 16
for THREADS in {1..16}; do
    echo "Running with $THREADS threads..."
    export OMP_NUM_THREADS=$THREADS
    
    # Record the start time
    START_TIME=$(date +%s.%N)
    
    # Run the executable
    $EXECUTABLE > /dev/null 2>&1
    
    # Record the end time
    END_TIME=$(date +%s.%N)
    
    # Calculate the elapsed time
    ELAPSED_TIME=$(echo "$END_TIME - $START_TIME" | bc)
    
    # Output the results
    echo "Threads: $THREADS | Time: $ELAPSED_TIME seconds"
    echo "$THREADS | $ELAPSED_TIME" >> $OUTPUT_FILE
    echo "-----------------------------------"
done

echo "All runs completed. Results saved to $OUTPUT_FILE."
