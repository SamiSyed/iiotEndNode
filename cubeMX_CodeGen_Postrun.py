import os
import re

def remove_mx_subghz_call(file_path):
    """
    Removes the MX_SubGHz_Phy_Process() function call from the main loop in the given file
    while preserving newlines and overall formatting.
    """
    try:
        # Read the contents of the file
        with open(file_path, 'r') as file:
            content = file.readlines()

        # Define a regex to match the MX_SubGHz_Phy_Process() call
        pattern = re.compile(r'\s*MX_SubGHz_Phy_Process\(\);\s*')

        # Process each line, keeping all lines except the one with the function call
        modified_content = [
            line for line in content if not pattern.fullmatch(line)
        ]

        # Write the modified content back to the file
        with open(file_path, 'w') as file:
            file.writelines(modified_content)

        print(f"Successfully removed MX_SubGHz_Phy_Process() from {file_path}")

    except FileNotFoundError:
        print(f"Error: File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    # Path to the generated 'main.c' file (adjust as needed for your CubeMX project directory)
    project_dir = os.path.dirname(os.path.realpath(__file__))  # Directory containing the script
    main_c_path = os.path.join(project_dir, "Core", "Src", "main.c")

    # Remove the function call from the main.c file
    remove_mx_subghz_call(main_c_path)

if __name__ == "__main__":
    main()
