# -*- coding: utf-8 -*-
"""
Created on Mon Apr  1 18:19:38 2013

@author: matz
"""

import cvcommon
import cvtype
import datatype
import document
import generator
import package
import test

# abbreviations
dt = test.Default()

# initializations
initInCopy = document.Document((
    "{1}->initializeImage({0}->width(), {0}->height(), {0}->stride(), "
    "{1}->data(), {0}->pixelType());").format("src1CastedData", "dstCastedData"
))
initOutCopy = document.Document((
    "{1}->initializeImage({1}->width(), {1}->height(), {1}->stride(), "
    "{1}->data(), {0}->pixelType());").format("src1CastedData", "dstCastedData"
))
initInDdepth = document.Document((
    "runtime::Image::PixelType pixelType = cvsupport::computeOutPixelType("
    "convertDdepth(m_ddepth), src1CastedData->pixelType());\n"
    "unsigned int stride = runtime::Image::pixelSize(pixelType) * "
    "src1CastedData->width();\n"
    "{1}->initializeImage({0}->width(), {0}->height(), stride, "
    "{1}->data(), pixelType);").format("src1CastedData", "dstCastedData"
))
initOutDdepth = document.Document((
    "runtime::Image::PixelType pixelType = cvsupport::computeOutPixelType("
    "convertDdepth(m_ddepth), src1CastedData->pixelType());\n"
    "unsigned int stride = runtime::Image::pixelSize(pixelType) * "
    "src1CastedData->width();\n"
    "{1}->initializeImage({1}->width(), {1}->height(), stride, "
    "{1}->data(), pixelType);").format("src1CastedData", "dstCastedData"
))
pixelTypeCheck = document.Document(
"""
if((src1CastedData->rows() != src2CastedData->rows()) || (src1CastedData->cols() != src2CastedData->cols()))
    throw runtime::InputError(SRC_1, *this, "Input images must have the same size.");
    
if(src1CastedData->numChannels() != src2CastedData->numChannels())
    throw runtime::InputError(SRC_1, *this, "Input images must have the same number of channels.");
    
if(src1CastedData->depth() != src2CastedData->depth())
    throw runtime::InputError(SRC_1, *this, "Input images must have the same depth if the destination depth is not explicitely given.");
""")
pixelTypeDdepthCheck = document.Document(
"""
if((src1CastedData->rows() != src2CastedData->rows()) || (src1CastedData->cols() != src2CastedData->cols()))
    throw runtime::InputError(SRC_1, *this, "Input images must have the same size.");
    
if(src1CastedData->numChannels() != src2CastedData->numChannels())
    throw runtime::InputError(SRC_1, *this, "Input images must have the same number of channels.");
    
if(m_ddepth == SAME && (src1CastedData->depth() != src2CastedData->depth()))
    throw runtime::InputError(SRC_1, *this, "Input images must have the same depth if the destination depth is not explicitely given.");
""")

# arguments
srcImg1 = package.Argument(
    "src1", "Source 1", cvtype.Mat(), datatype.Image()
)
srcImg2 = package.Argument(
    "src2", "Source 2", cvtype.Mat(), datatype.Image()
)
dstImgDdepth = package.Argument(
    "dst", "Destination", cvtype.Mat(), datatype.Image(), initIn = initInDdepth,
    initOut = initOutDdepth
)
dstImg = package.Argument(
    "dst", "Destination", cvtype.Mat(), datatype.Image(), initIn = initInCopy,
    initOut = initOutCopy
)
descriptions = [
    package.EnumDescription("SAME", "Same as inputs", -1),
    package.EnumDescription("DEPTH_8_BIT", "8-bit", "CV_8U"),
    package.EnumDescription("DEPTH_16_BIT", "16-bit", "CV_16U")
]
ddepth = package.EnumParameter(
    "ddepth", "Destination depth", descriptions = descriptions,
    default = 0
)
noArray = package.Constant("cv::noArray()")
alpha = package.NumericParameter(
    "alpha", "Alpha", cvtype.Float64(), datatype.Float64(), default = 1.0
)
beta = package.NumericParameter(
    "beta", "Beta", cvtype.Float64(), datatype.Float64(), default = 1.0
)
gamma = package.NumericParameter(
    "gamma", "Gamma", cvtype.Float64(), datatype.Float64(), default = 1.0
)

# test data
lenna = test.ImageFile("lenna.jpg")
barbara = test.ImageFile("barbara.jpg")
lenna_16bit = test.ImageFile("lenna.jpg", deepColor = True)
barbara_16bit = test.ImageFile("barbara.jpg", deepColor = True)
barbara = test.ImageFile("barbara.jpg")
lenna_bw = test.ImageFile("lenna.jpg", grayscale = True)
barbara_bw = test.ImageFile("barbara.jpg", grayscale = True)
memory = test.ImageBuffer(5000000)

# absdiff
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Input(srcImg2), package.Output(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna, barbara, memory],
        [lenna_bw, barbara_bw, memory]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Input(srcImg2), package.Allocation(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna_16bit, barbara_16bit, dt]
    ]
)
absdiff = package.Method(
    "absdiff", options = [manual, allocate]
)

# add
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Input(srcImg2), package.Output(dstImgDdepth),
     noArray, ddepth],
    inputCheck = pixelTypeDdepthCheck,
    tests = [
        [lenna, barbara, memory, dt, dt],
        [lenna_bw, barbara_bw, memory, dt, dt],
        [lenna_16bit, barbara, memory, dt, 1]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Input(srcImg2),
     package.Allocation(dstImgDdepth), noArray, ddepth],
    inputCheck = pixelTypeDdepthCheck,
    tests = [
        [lenna_16bit, barbara_16bit, dt, dt, dt],
        [lenna_16bit, barbara, dt, dt, 2]
    ]
)
add = package.Method(
    "add", options = [manual, allocate]
)

# addWeighted
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), alpha, package.Input(srcImg2),
     beta, gamma, package.Output(dstImgDdepth), ddepth],
    inputCheck = pixelTypeDdepthCheck,
    tests = [
        [lenna, dt, barbara, dt, dt, memory, dt],
        [lenna_bw, 2.0, barbara_bw, 0.5, 3.0, memory, dt],
        [lenna_16bit, 1.0, barbara, 0.5, -10, memory, 1]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), alpha, package.Input(srcImg2),
     beta, gamma, package.Allocation(dstImgDdepth), ddepth],
    inputCheck = pixelTypeDdepthCheck,
    tests = [
        [lenna_16bit, -1.0, barbara_16bit, 10.0, 2.0, dt, dt],
        [lenna_16bit, -10.0, barbara, 2.0, 0.0, dt, 2]
    ]
)
addWeighted = package.Method(
    "addWeighted", options = [manual, allocate]
)

# bitwise_and
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Input(srcImg2), package.Output(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna, barbara, memory],
        [lenna_bw, barbara_bw, memory]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Input(srcImg2), package.Allocation(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna_16bit, barbara_16bit, dt]
    ]
)
bitwise_and = package.Method(
    "bitwise_and", options = [manual, allocate]
)

# bitwise_not
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Output(dstImg)],
    tests = [
        [lenna, memory],
        [lenna_bw, memory]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Allocation(dstImg)],
    tests = [
        [lenna_16bit, dt]
    ]
)
bitwise_not = package.Method(
    "bitwise_not", options = [manual, allocate]
)

# bitwise_or
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Input(srcImg2), package.Output(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna, barbara, memory],
        [lenna_bw, barbara_bw, memory]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Input(srcImg2), package.Allocation(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna_16bit, barbara_16bit, dt]
    ]
)
bitwise_or = package.Method(
    "bitwise_or", options = [manual, allocate]
)

# bitwise_xor
manual = package.Option(
    "manual", "Manual", 
    [package.Input(srcImg1), package.Input(srcImg2), package.Output(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna, barbara, memory],
        [lenna_bw, barbara_bw, memory]
    ]
)
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(srcImg1), package.Input(srcImg2), package.Allocation(dstImg)],
    inputCheck = pixelTypeCheck,
    tests = [
        [lenna_16bit, barbara_16bit, dt]
    ]
)
bitwise_xor = package.Method(
    "bitwise_xor", options = [manual, allocate]
)

core = package.Package(
    "cvcore", 0, 0, 1,
    methods = [
        absdiff,
        add,
        addWeighted,
        bitwise_and,
        bitwise_not,
        bitwise_or,
        bitwise_xor
    ],
    functions = [
        cvcommon.checkEnumValue,
        cvcommon.checkNumericValue
    ],
    testFiles = [
        "barbara.jpg",
        "lenna.jpg"
    ]
)


generator.generateMethodFiles(core, bitwise_xor)
generator.generatePackageFiles(core) 