import subprocess


def binexec(filename):
    out = subprocess.check_output([
        './cola.out', 'tests/output_tests/code/{}'.format(filename)
    ])

    if out:
        return out[:-1] if out[len(out) - 1] == '\n' else out
    else:
        return None
