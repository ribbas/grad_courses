# release.py
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Release Python script

from os import listdir, path
import subprocess
import sys

if __name__ == "__main__":

    if len(sys.argv) == 2:

        command = ["tar", "-cvf"]
        tarfile_name = ""
        arch_files = None
        cur_dir = path.dirname(path.abspath(__file__))

        if sys.argv[-1] == "-b":
            confirm = raw_input("Generate a binary release? [Y/n]: ")
            if confirm.lower() == "y":
                host_name = raw_input("Please enter a hostname: ")

                tarfile_name = "homework1_" + host_name + ".tar"
                arch_files = [path.join(cur_dir, "bin")]

            else:
                print("Binary release generation cancelled")
                exit(0)

        elif sys.argv[-1] == "-s":
            confirm = raw_input("Generate a source release? [Y/n]: ")
            if confirm.lower() == "y":

                make_clean_cmd = ["make", "clean"]
                subprocess.run(make_clean_cmd)

                tarfile_name = "homework1.tar"
                arch_files = listdir(cur_dir)

            else:
                print("Source release generation cancelled")
                exit(0)

        else:
            print("Invalid arguments")
            exit(0)

        command.append(tarfile_name)
        command.extend(arch_files)
        subprocess.run(command)
