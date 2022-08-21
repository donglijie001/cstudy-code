https://aiden-dong.gitee.io/2019/07/20/CMake%E6%95%99%E7%A8%8B%E4%B9%8BCMake%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E5%BA%94%E7%94%A8/


vscode debug ：https://zhuanlan.zhihu.com/p/398428136
tasks.json 内容
```
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [{
        "label": "cbuild",
        "command": "gcc",
        "args": [
            "-g",
            "${file}",
            "-o",
            "${fileDirname}/${fileBasenameNoExtension}.out"
        ],
        "type": "shell",
        "problemMatcher": []
    }]
}
//调试（fn + F5）
//下一步（fn + 10）
//重启（shift+fn+F5）
//继续（fn +F5）
```
launch.json 内容
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(lldb) Launch", // 配置名称，将会在调试配置下拉列表中显示
            "type": "cppdbg", // 调试器类型：Windows表示器使用cppvsdbg；GDB和LLDB使用cppdbg。该值自动生成
            "request": "launch", // 调试方式
            "program": "${fileDirname}/${fileBasenameNoExtension}.out", // 要调试的程序（完整路径，支持相对路径）
            "args": [], // 传递给上面程序的参数，没有参数留空即可
            // "stopAtEntry": false, // 是否停在程序入口点（即停在main函数开始）（目前为不停下）
            "stopAtEntry": true,
            "cwd": "${workspaceRoot}", // 调试程序时的工作目录
            "environment": [],
            "externalConsole": false, // 调试时是否显示控制台窗口(目前为不显示)
            "preLaunchTask": "cbuild", //预先执行task.json
            "MIMode": "lldb" //MAC下的debug程序
        }
    ]
}
```