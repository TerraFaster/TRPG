import os

def count_lines_symbols(file_path, remove_whitespace=False):
    """Count lines and symbols in a file, with an option to ignore whitespace."""
    lines_count = 0
    symbols_count = 0

    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        for line in file:
            if remove_whitespace:
                line = line.strip()
                if not line:
                    continue  # Ignore blank lines if whitespace removal is enabled
            lines_count += 1
            symbols_count += len(line)

    return lines_count, symbols_count

def process_directory(directory, file_types=None, remove_whitespace=False):
    """Process a directory recursively and count lines and symbols in files."""
    total_directories = 0
    total_files = 0

    total_lines = 0
    total_symbols = 0

    for root, _, files in os.walk(directory):
        for file_name in files:
            # Check file type if file_types is specified
            if file_types and not any(file_name.endswith(ft) for ft in file_types):
                continue
            
            file_path = os.path.join(root, file_name)
            try:
                lines, symbols = count_lines_symbols(file_path, remove_whitespace)
                total_lines += lines
                total_symbols += symbols

                total_files += 1
            except Exception as e:
                print(f"Error reading {file_path}: {e}")

        total_directories += 1

    return total_directories, total_files, total_lines, total_symbols

def main(directories, file_types=None):
    """Main function to iterate through directories and calculate totals."""
    total_directories = 0
    total_files = 0

    total_lines = 0
    total_symbols = 0
    total_lines_trimmed = 0
    total_symbols_trimmed = 0

    # Process each directory in the list
    for directory in directories:
        print(f"\nProcessing directory: {directory}")
        
        # Regular counts
        proc_directories, proc_files, lines, symbols = process_directory(directory, file_types)
        total_directories += proc_directories
        total_files += proc_files
        total_lines += lines
        total_symbols += symbols
        print(f"  Total (with whitespace): {lines} lines, {symbols} symbols")

        # Counts with whitespace removed
        proc_directories, proc_files, lines_trimmed, symbols_trimmed = process_directory(directory, file_types, remove_whitespace=True)
        total_lines_trimmed += lines_trimmed
        total_symbols_trimmed += symbols_trimmed
        print(f"  Total (whitespace removed): {lines_trimmed} lines, {symbols_trimmed} symbols")

    print("\nSummary:")
    print(f"Total directories processed: {total_directories}")
    print(f"Total files processed: {total_files}")
    print(f"\nTotal lines (with whitespace): {total_lines}")
    print(f"Total symbols (with whitespace): {total_symbols}")
    print(f"\nTotal lines (whitespace removed): {total_lines_trimmed}")
    print(f"Total symbols (whitespace removed): {total_symbols_trimmed}")

if __name__ == "__main__":
    # Example usage:
    directories_to_check = [
        "./src", 
    ]  # List of directories to check
    file_extensions = [".h", ".cpp"]  # Specify file types or set to None for all files

    main(directories=directories_to_check, file_types=file_extensions)
