#
# release.py
#
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Release script for the project. This file archives the files and binaries of
# the project into a tar.
#

import subprocess
import sys

if __name__ == "__main__":

    # if argument is provided
    if len(sys.argv) == 2:

        # tar command list
        tar_command: list = ["tar", "-cvf"]
        # name of output tarfile
        tarfile_name: str = ""
        # files to archive
        arch_files: list = None
        # current directory
        cur_dir: str = "homework2"

        # if user prompts for a binary release
        if sys.argv[-1] == "-b":
            confirm = input("Generate a binary release? [Y/n]: ")
            if confirm.lower() == "y":
                host_name: str = input("Please enter a hostname: ")
                tarfile_name: str = f"{cur_dir}_{host_name}.tar"

                arch_files = [f"../{cur_dir}/bin"]

            else:
                print("Binary release generation cancelled")
                exit(0)

        # if user prompts for a source release
        elif sys.argv[-1] == "-s":
            confirm = input("Generate a source release? [Y/n]: ")
            if confirm.lower() == "y":
                tarfile_name = f"{cur_dir}.tar"

                # run `make clean`
                make_clean_cmd: list = ["make", "clean"]
                subprocess.run(make_clean_cmd)

                arch_files = [f"../{cur_dir}"]

            else:
                print("Source release generation cancelled")
                exit(0)

        else:
            print("Invalid arguments")
            exit(0)

        # construct and run the tar command
        tar_command.append(tarfile_name)
        tar_command.extend(arch_files)
        subprocess.Popen(tar_command)
