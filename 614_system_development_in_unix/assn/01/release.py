# release.py
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Release Python script

from pathlib import Path
import subprocess
import sys
from typing import Union

if __name__ == "__main__":

    if len(sys.argv) == 2:

        command: list = ["tar", "-cvf"]
        tarfile_name: str = ""
        arch_files: Union[Path, str] = None
        cur_dir: Path = Path(__file__).parent

        if sys.argv[-1] == "-b":
            confirm = input("Generate a binary release? [Y/n]: ")
            if confirm.lower() == "y":
                host_name: str = input("Please enter a hostname: ")
                tarfile_name: str = f"homework1_{host_name}.tar"

                arch_files = [cur_dir / "bin"]

            else:
                print("Binary release generation cancelled")
                exit(0)

        elif sys.argv[-1] == "-s":
            confirm = input("Generate a source release? [Y/n]: ")
            if confirm.lower() == "y":
                tarfile_name = "homework1.tar"

                make_clean_cmd: list = ["make", "clean"]
                subprocess.run(make_clean_cmd)

                arch_files = list(i.name for i in cur_dir.iterdir())

            else:
                print("Source release generation cancelled")
                exit(0)

        else:
            print("Invalid arguments")
            exit(0)

        command.append(tarfile_name)
        command.extend(arch_files)
        print(command)
        subprocess.run(command)
