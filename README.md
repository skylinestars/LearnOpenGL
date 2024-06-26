# LearnOpenGL
CPU给GPU下达一次渲染指令叫Drawcall

### 什么是图形渲染管线

> 一堆原始图形数据途径一个输送管道，期间经过各种变化处理最终出现在屏幕上的过程。
>
> 主要包括两个功能：一是将物体3D坐标转变为屏幕空间2D坐标，二是为屏幕每个像素点进行着色。

分三个阶段：应用程序阶段、几何阶段、光栅化阶段。

1、应用程序阶段：

CPU将GPU渲染需要的**模型（顶点坐标、法线坐标、纹理坐标等）、灯光准备好，并设置好渲染状态**，为GPU渲染做好准备。

2、几何阶段：

> 顶点着色器、曲面细分、几何着色器、图元组装（裁剪剔除、屏幕映射）、

把输入的3D数据转化为2D数据。

**顶点着色器**：进行顶点坐标变换，将顶点坐标从**模型空间**转换到**剪裁空间**。顶点着色器可以具有用户定义的输出，但也有一个特殊的输出来表示顶点的最终位置。如果没有后续的顶点处理阶段，则顶点着色器应使用顶点的剪辑空间位置填充此位置，以便进行渲染。

**曲面细分**：输入是新图元**patch**，是利用细分处理技术对三角面进行细分，以此来增加物体表面的三角面的数量，是渲染管线一个可选的阶段。动态的调整模型的复杂度。我们可以借助曲面细分的技术实现LOD(Level-of-Detail)的机制，使得离摄像机越近的物体具有更加丰富的细节，而远离摄像机的物体具有较少的细节。（D3D11 术语中的 Hull Shader 和 Domain Shader，OpenGL 4.0 术语中的 Tessellation Control Shader 和 Tessellation Evaluation Shader）

1、海浪、雪地

2、与置换贴图（也叫位移贴图）结合，比法线贴图更真实。

**几何着色器**：几何着色器也是渲染管线一个可选的阶段。几何着色器的输入是一个图元（如点或三角形）的一组顶点，输出是零个或多个简单图元。

1、几何动画

2、草地（结合曲面细分）

**图元装配**：图元组装将输入的顶点组装成指定的图元。图元组装阶段会进行裁剪和背面剔除相关的优化，以减少进入光栅化的图元的数量，加速渲染过程。

在光栅化之前，还会进行屏幕映射的操作：透视除法和视口变换。关于透视除法和视口变换到底属于流水线的那个阶段并没有一个权威的说法，某些资料将这两个操作归入到图元组装阶段，某些资料将它归入到光栅化过程，但对我们理解整个渲染管线并没有太大的影响，**我们只需要知道在光栅化前需要进行屏幕映射就可以了**，所以我们这里将屏幕映射放到了图元组装过程。这两个操作主要是硬件实现，不同厂商会有不同的设计。

3、光栅化阶段：

把图元映射为最终屏幕上的颜色。包括光栅化、片段着色、测试混合阶段。

**光栅化**：就是找到所有被几何图元所占据的所有像素点（找到这些像素点之后再进行逐个渲染）。包括三角形组装和三角形遍历两个阶段。

**片段着色器**：计算每个像素的颜色。在这个阶段会进行光照计算以及阴影处理，是渲染管线高级效果产生的地方。

**测试混合阶段**：管线的最后一个阶段是测试混合阶段。测试包括裁切测试、Alpha测试、模板测试和深度测试。没有经过测试的片段会被丢弃，不需要进行混合阶段；经过测试的片段会进入混合阶段。Alpha混合可以根据片段的alpha值进行混合，用来产生半透明的效果。测试混合阶段虽然不是可编程阶段，但是我们可以通过OpenGL或DirectX提供的接口进行配置，定制混合和测试的方式。

值得注意的是，半透明物体的绘制需要遵循[画家算法(painter Algorithm)](https://link.zhihu.com/?target=https%3A//en.wikipedia.org/wiki/Painter%27s_algorithm)由远及近进行绘制，因为半透明的混合跟物体的顺序有严格的对应关系。从下面两张图我们可以看到，先绘制红色还是先绘制绿色对最终颜色的有这很大的影响。所以，绘制半透明物体之前，我们需要按照距离远近对场景中的物体进行严格排序，然而这是一个非常棘手的问题。

4、最终渲染好的颜色先被送入后置缓冲，随后再替换前置缓冲，显示在屏幕上



### 纹理

###### 纹理环绕方式

| 环绕方式           | 描述                                                         |
| :----------------- | :----------------------------------------------------------- |
| GL_REPEAT          | 对纹理的默认行为。重复纹理图像。                             |
| GL_MIRRORED_REPEAT | 和GL_REPEAT一样，但每次重复图片是镜像放置的。                |
| GL_CLAMP_TO_EDGE   | 纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。 |
| GL_CLAMP_TO_BORDER | 超出的坐标为用户指定的边缘颜色。                             |

###### 纹理过滤

1、GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。

2、GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。

###### 不同多级渐远纹理级别之间的过滤方式

| GL_NEAREST_MIPMAP_NEAREST | 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样 |
| ------------------------- | ------------------------------------------------------------ |
| GL_LINEAR_MIPMAP_NEAREST  | 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样         |
| GL_NEAREST_MIPMAP_LINEAR  | 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样 |
| GL_LINEAR_MIPMAP_LINEAR   | 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样 |

### VAO、VBO、EBO

VAO：顶点数组对象

VBO：顶点缓存对象

EBO：元素（索引）缓存对象

![vertex_array_objects_ebo](C:\Users\DELL\Pictures\Saved Pictures\vertex_array_objects_ebo.png)



```c++
unsigned int VBO, VAO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

//绑定VAO
glBindVertexArray(VAO);
//绑定VBO、并填充数据
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//绑定EBO、并填充数据
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//指定顶点存储位置
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

### 合批

动态合批与静态合批其本质是对将多次绘制请求，在允许的条件下进行合并处理，减少 CPU 对 GPU 绘制请求的次数，达到提高性能的目的。

批量渲染是通过减少CPU向GPU发送渲染命令（DrawCall）的次数，以及减少GPU切换渲染状态的次数，尽量让GPU一次多做一些事情，来提升逻辑线和渲染线的整体效率。
但这是建立在GPU相对空闲，而CPU把更多的时间都耗费在渲染命令的提交上时，才有意义。

**SRP Batcher 通过批处理一系列 Bind 和 Draw GPU 命令来减少 DrawCall 之间的 GPU 设置的工作量**。也就是之前一堆绑定和绘制的 GPU 命令，我们可以使用批处理减少绘制调用之间的 GPU 设置

### GPU实例化

GPU Instancing 的处理过程是**只提交一个模型网格让GPU绘制很多个地方，这些不同地方绘制的网格可以对缩放大小，旋转角度和坐标有不一样的操作，材质球虽然相同但材质球属性可以各自有各自的区别。**



### 多线程渲染

多线程渲染其实是指将渲染单独放到一个线程，理论上可以开启不止一个线程来执行渲染指令，但是Opengl并不支持多个线程同时操作同一个Context

- 在主线程中调用的图形API被封装成命令，提交到渲染队列，这样就可以节省在主线程中调用图形API的开销，从而提高帧率
- 渲染线程从渲染队列获取渲染指令并执行调用图形API与驱动层交互，这部分交互耗时从主线程转到渲染线程
