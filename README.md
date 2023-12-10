# LearnOpenGL
### 什么是图形渲染管线

> 一堆原始图形数据途径一个输送管道，期间经过各种变化处理最总出现在屏幕上的过程。

1、把3D坐标装换为2D坐标。

2、把2D坐标转变为实际有颜色的像素。

###### 具体部分

1、顶点着色器

> 它把一个单独的顶点作为输入。顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释），同时顶点着色器允许我们对顶点属性进行一些基本处理。

2、图元装配

> 顶点着色器的输出作为输入，并将所有的点装配成指定的形状。

3、几何着色器

> 通过产生新的顶点构造出新的图元来生成其他形状。

4、光栅化阶段

> 把图元映射为最终屏幕上的像素，生成供片段着色器使用的片段。

5、剪裁

6、片段着色器

> 计算一个像素的最总颜色。使用光照、阴影、光的颜色等场景数据计算最终的颜色

7、Alpha测试、混合阶段

> 这个阶段检测片段的对应的深度（和模板(Stencil)）值（后面会讲），用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃。这个阶段也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)。所以，即使在片段着色器中计算出来了一个像素输出的颜色，在渲染多个三角形的时候最后的像素颜色也可能完全不同。



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
