# 查询手册

[OpenGL 4.5 指南](https://www.khronos.org/registry/OpenGL-Refpages/gl4/)

## 前言

### 涉及的相关学科知识

数学知识（线性代数、几何、三角学）

### 相关的名词术语

#### 着色器：shader

`着色器`是使用一种叫`GLSL`的**类C语言**写成的。GLSL是为图形计算量身定制的，它包含**一些针对向量和矩阵操作**的有用特性。

着色器的开头总是要**声明版本**，接着是**输入和输出变量**、**uniform**和**main函数**。

每个着色器的入口点都是main函数，在这个函数中我们处理所有的输入变量，并将结果输出到输出变量中。

#### 向量：vec

|  类型   | 含义                            |
| :-----: | ------------------------------- |
| `vecn`  | 包含`n`个float分量的默认向量    |
| `bvecn` | 包含`n`个bool分量的向量         |
| `ivecn` | 包含`n`个int分量的向量          |
| `uvecn` | 包含`n`个unsigned int分量的向量 |
| `dvecn` | 包含`n`个double分量的向量       |

一个向量的分量可以通过`vec.x`这种方式获取，这里`x`是指这个向量的第一个分量。你可以分别使用`.x`、`.y`、`.z`和`.w`来获取它们的第1、2、3、4个分量。

GLSL也允许你对颜色使用`rgba`，或是对纹理坐标使用`stpq`访问相同的分量。

#### 输入与输出：layout

GLSL定义了`in`和`out`关键字专门来实现着色器的输入与输出。

顶点着色器的输入特殊在，它**从顶点数据中直接接收输入**。为了定义顶点数据该如何管理，我们使用`location`这一元数据指定输入变量，这样我们才可以在CPU上配置顶点属性，如 `layout (location = 0)`。

片段着色器需要一个`vec4`颜色输出变量，因为片段着色器需要生成一个最终输出的颜色。如果你在片段着色器没有定义输出颜色，OpenGL会把你的物体渲染为黑色（或白色）。

#### Uniform变量

Uniform是一种从CPU中的应用向GPU中的着色器发送数据的方式，但uniform和顶点属性有些不同。

首先，uniform是全局的(Global)。全局意味着uniform变量必须在每个着色器程序对象中都是独一无二的，而且它可以被着色器程序的任意着色器在任意阶段访问。

第二，无论你把uniform值设置成什么，uniform会一直保存它们的数据，直到它们被重置或更新。

## GLSL

### 声明

### 内置变量

#### gl_GlobalInvocationID

> contains the global index of work item currently being operated on by a compute shader
>
> 包含当前由计算着色器操作的工作项的全局索引

##### 声明

```glsl
in uvec3 gl_GlobalInvocationID ;
```

##### 描述

在计算着色器中，gl_GlobalInvocationID是派生的输入变量，其中包含当前着色器正在其上执行的全局工作组中工作调用的n维索引。 gl_GlobalInvocationID的值等于``gl_WorkGroupID * gl_WorkGroupSize + gl_LocalInvocationID`。

##### 版本支持

v4.30及以上

### 内置函数

#### all

> check whether all elements of a boolean vector are true
>
> 检查布尔向量的所有元素是否都为真

##### 声明

```glsl
bool all(	bvec x);
```

##### 版本支持

v1.10及以上

#### clamp

> constrain a value to lie between two further values
>
> 将一个值约束在两个其他值之间

##### 声明

```glsl
genType clamp(genType x, genType minVal, genType maxVal);
genType clamp(genType x, float minVal, float maxVal);
 
genDType clamp(genDType x, genDType minVal, genDType maxVal);
genDType clamp(genDType x, double minVal, double maxVal);
 
genIType clamp(genIType x, genIType minVal, genIType maxVal);
genIType clamp(genIType x, int minVal, int maxVal);
 
genUType clamp(genUType x, genUType minVal, genUType maxVal);
genUType clamp(genUType x, uint minVal, uint maxVal);
```

##### 描述

返回的值计算为：`min(max(x，minVal), maxVal)`

#### floatBitsToInt

> produce the encoding of a floating point value as an integer
>
> 将浮点值编码为整数

##### 声明

```glsl
genIType floatBitsToInt(genType x);
genUType floatBitsToUint(genType x);
```

##### 版本支持

v3.30及以上

#### imageLoad

> load a single texel from an image
>
> 从图像加载单个纹理像素

##### 声明

```glsl
gvec4 imageLoad(gimage1D image, int P);
gvec4 imageLoad(gimage2D image, ivec2 P);
gvec4 imageLoad(gimage3D image, ivec3 P);
```

##### 版本支持

v4.20及以上

#### intBitsToFloat

> uintBitsToFloat — produce a floating point using an encoding supplied as an integer
>
> 使用作为整数提供的编码生成浮点

##### 声明

```glsl
genType intBitsToFloat(genIType x);
genType uintBitsToFloat(genUType x);
```

##### 版本支持

v3.30及以上

#### imageStore

> write a single texel into an image
>
> 将单个纹理像素写入图像

##### 声明

```glsl

void imageStore(gimage1D image, int P, gvec4 data);
void imageStore(gimage2D image, ivec2 P, gvec4 data);
void imageStore(gimage3D image, ivec3 P, vec4 data);
```

##### 版本支持

v4.20及以上

#### lessThan

> perform a component-wise less-than comparison of two vectors, returns a boolean vector in which each element *i* is computed as *`x`*[*i*] < *`y`*[*i*].
>
> 对两个向量执行逐分量小于比较，返回一个布尔向量，其中每个元素i的计算公式为x [i] <y [i]。

##### 声明

```glsl
bvec lessThan(vec x, vec y);
bvec lessThan(ivec x, ivec y);
bvec lessThan(uvec x, uvec y);
```

##### 版本支持

v1.30及以上

#### mix

> linearly interpolate between two values
>
> 在两个值之间线性插值

##### 描述

GLSL内建的mix函数**需要接受两个值作为参数，并对它们根据第三个参数进行线性插值**。

- 如果第三个值是0.0，它会返回第一个输入；
- 如果是1.0，会返回第二个输入值;
- 0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。

#### mod

> compute value of one parameter modulo another
>
> 计算一个参数取模的值

##### 声明

```glsl
genType mod(genType x, float y); 
genType mod(genType x, genType y);
genDType mod(genDType x, double y);
genDType mod(genDType x, genDType y);
```

##### 描述

返回 `x % y` 的结果，计算公式为：`x -y * floor(x / y)`。

#### step

> generate a step function by comparing two values
>
> 通过比较两个值生成阶跃函数

##### 声明

```glsl
genType step(genType edge, genType x);
genType step(float edge, genType x);
genDType step(genDType edge, genDType x);
genDType step(double edge, genDType x);
```

##### 参数

**`edge`**

Specifies the location of the edge of the step function.

指定步进功能边缘的位置。

**`x`**

Specify the value to be used to generate the step function.

指定用于生成步进函数的值。

#### texelFetch

> perform a lookup of a single texel within a texture.
>
> 在纹理内执行单个纹理像素的查找.

从绑定到采样器的纹理中的纹理坐标P执行单个纹理像素的查找，返回纹理像素中的某个样本。

##### 声明

```glsl
gvec4 texelFetch(gsampler1D sampler, int P, int lod);
gvec4 texelFetch(gsampler2D sampler, ivec2 P, int lod);
gvec4 texelFetch(gsampler3D sampler, ivec3 P, int lod);
```

##### 参数

**`sampler`**

Specifies the sampler to which the texture from which texels will be retrieved is bound.

指定从中检索纹理像素的纹理绑定到的采样器。

**`P`**

Specifies the texture coordinates at which texture will be sampled.

指定要对纹理进行采样的纹理坐标。

**`lod`**

If present, specifies the level-of-detail within the texture from which the texel will be fetched.

如果存在，则指定纹理中的详细程度，从中将提取纹理像素。

##### 版本支持

v1.30及以上