import subprocess


def main() -> None:
    result = subprocess.run(
        ["build.bat"], capture_output=True, text=True, shell=True
    )

    if result.returncode == 0:
        print("Batch file ran successfully")
    else:
        print("Batch file failed with return code", result.returncode)

    output_lines = result.stdout.splitlines()

    for line in output_lines:
        if (
            r"C:\Program Files" in line
            or "unreferenced inline function has been removed" in line
        ):
            continue
        print(line)


if __name__ == "__main__":
    main()
