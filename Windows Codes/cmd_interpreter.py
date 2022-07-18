def main():
    cmds = {'dir': dir_proc, 'cls': cls_proc, 'copy': copy_proc}

    while True:
        s = input('CSD>')
        params = cmd_text.split()
        if params[0] in cmds:
            cmds[params[0]]()
        else:
            print('command not found: {params[0]}')

def dir_proc():
    print('dir_proc')

def cls_proc():
    print('cls_proc')

def copy_proc():
    print('copy')

main()
