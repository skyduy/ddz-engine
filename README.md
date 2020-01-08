# 斗地主引擎
>获取所有可能出牌方式

## 使用说明


- 安装依赖项 `conda install pybind11` （注意`pip install`不行，因为不会安装下面`cmake`操作中所需要的`.cmake`文件，如果你没装anaconda，就去官网自己下载pybind11，然后`build, cmake, make install`）

- 运行
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

- 会根据自己系统环境在`build`创建相应项目，然后

    - Windows下的话，用vs打开`ddz.sln`，然后build一个`x64`的`Release`方案即可

    - \*Unix 没试过

- 然后，Windows下在`build/Release`目录下会有一个`ddz.xxx.pyd`文件，将该文件所在目录添加至PYTHONPATH，`import ddz`即可导入并使用。效果如下：

    ![效果图](https://github.com/skyduy/ddz_moves/blob/master/%E6%95%88%E6%9E%9C.jpg)