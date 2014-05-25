xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,-0.000000,1.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Frame Mesh_002 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
423;
0.000500; 0.061800; 2.578900;,
0.046700; 0.043500; 2.501000;,
0.092900; 0.061800; 2.578900;,
0.000500; 0.061800; 2.578900;,
-0.092000; 0.061800; 2.578900;,
-0.045800; 0.043500; 2.501000;,
-0.045800; 0.043500; 2.501000;,
0.046700; 0.043500; 2.501000;,
0.000500; 0.061800; 2.578900;,
0.046700; 0.043500; 2.501000;,
0.046700; 0.619900; 2.365300;,
0.092900; 0.638200; 2.443200;,
0.092900; 0.061800; 2.578900;,
0.092900; 0.061800; 2.578900;,
0.092900; 0.638200; 2.443200;,
0.046700; 0.656600; 2.521100;,
0.046700; 0.080200; 2.656900;,
0.046700; 0.080200; 2.656900;,
0.046700; 0.656600; 2.521100;,
-0.045800; 0.656600; 2.521100;,
-0.045800; 0.080200; 2.656900;,
-0.045800; 0.080200; 2.656900;,
-0.045800; 0.656600; 2.521100;,
-0.092000; 0.638200; 2.443200;,
-0.092000; 0.061800; 2.578900;,
-0.092000; 0.061800; 2.578900;,
-0.092000; 0.638200; 2.443200;,
-0.045800; 0.619900; 2.365300;,
-0.045800; 0.043500; 2.501000;,
0.046700; 0.619900; 2.365300;,
0.046700; 0.043500; 2.501000;,
-0.045800; 0.043500; 2.501000;,
-0.045800; 0.619900; 2.365300;,
0.046700; 0.619900; 2.365300;,
-0.045800; 0.619900; 2.365300;,
-0.063300; 0.612900; 2.335700;,
0.064200; 0.612900; 2.335700;,
-0.045800; 0.619900; 2.365300;,
-0.092000; 0.638200; 2.443200;,
-0.127000; 0.638200; 2.443200;,
-0.063300; 0.612900; 2.335700;,
-0.092000; 0.638200; 2.443200;,
-0.045800; 0.656600; 2.521100;,
-0.063300; 0.663500; 2.550700;,
-0.127000; 0.638200; 2.443200;,
-0.045800; 0.656600; 2.521100;,
0.046700; 0.656600; 2.521100;,
0.064200; 0.663500; 2.550700;,
-0.063300; 0.663500; 2.550700;,
0.046700; 0.656600; 2.521100;,
0.092900; 0.638200; 2.443200;,
0.128000; 0.638200; 2.443200;,
0.064200; 0.663500; 2.550700;,
0.092900; 0.638200; 2.443200;,
0.046700; 0.619900; 2.365300;,
0.064200; 0.612900; 2.335700;,
0.128000; 0.638200; 2.443200;,
0.128000; 0.638200; 2.443200;,
0.064200; 0.612900; 2.335700;,
0.064200; 0.802000; 2.291200;,
0.128000; 0.827300; 2.398700;,
0.064200; 0.663500; 2.550700;,
0.128000; 0.638200; 2.443200;,
0.128000; 0.827300; 2.398700;,
0.064200; 0.852700; 2.506200;,
-0.063300; 0.663500; 2.550700;,
0.064200; 0.663500; 2.550700;,
0.064200; 0.852700; 2.506200;,
-0.063300; 0.852700; 2.506200;,
-0.127000; 0.638200; 2.443200;,
-0.063300; 0.663500; 2.550700;,
-0.063300; 0.852700; 2.506200;,
-0.127000; 0.827300; 2.398700;,
-0.063300; 0.612900; 2.335700;,
-0.127000; 0.638200; 2.443200;,
-0.127000; 0.827300; 2.398700;,
-0.063300; 0.802000; 2.291200;,
0.064200; 0.612900; 2.335700;,
-0.063300; 0.612900; 2.335700;,
-0.063300; 0.802000; 2.291200;,
0.064200; 0.802000; 2.291200;,
0.064200; 0.802000; 2.291200;,
-0.063300; 0.802000; 2.291200;,
-0.044700; 0.809400; 2.322600;,
0.045600; 0.809400; 2.322600;,
-0.063300; 0.802000; 2.291200;,
-0.127000; 0.827300; 2.398700;,
-0.089800; 0.827300; 2.398700;,
-0.044700; 0.809400; 2.322600;,
-0.127000; 0.827300; 2.398700;,
-0.063300; 0.852700; 2.506200;,
-0.044700; 0.845300; 2.474700;,
-0.089800; 0.827300; 2.398700;,
-0.063300; 0.852700; 2.506200;,
0.064200; 0.852700; 2.506200;,
0.045600; 0.845300; 2.474700;,
-0.044700; 0.845300; 2.474700;,
0.064200; 0.852700; 2.506200;,
0.128000; 0.827300; 2.398700;,
0.090700; 0.827300; 2.398700;,
0.045600; 0.845300; 2.474700;,
0.128000; 0.827300; 2.398700;,
0.064200; 0.802000; 2.291200;,
0.045600; 0.809400; 2.322600;,
0.090700; 0.827300; 2.398700;,
0.090700; 0.827300; 2.398700;,
0.045600; 0.809400; 2.322600;,
0.045600; 0.741900; 2.338500;,
0.090700; 0.759800; 2.414600;,
0.045600; 0.845300; 2.474700;,
0.090700; 0.827300; 2.398700;,
0.090700; 0.759800; 2.414600;,
0.045600; 0.777700; 2.490700;,
-0.044700; 0.845300; 2.474700;,
0.045600; 0.845300; 2.474700;,
0.045600; 0.777700; 2.490700;,
-0.044700; 0.777700; 2.490700;,
-0.089800; 0.827300; 2.398700;,
-0.044700; 0.845300; 2.474700;,
-0.044700; 0.777700; 2.490700;,
-0.089800; 0.759800; 2.414600;,
-0.044700; 0.809400; 2.322600;,
-0.089800; 0.827300; 2.398700;,
-0.089800; 0.759800; 2.414600;,
-0.044700; 0.741900; 2.338500;,
0.045600; 0.809400; 2.322600;,
-0.044700; 0.809400; 2.322600;,
-0.044700; 0.741900; 2.338500;,
0.045600; 0.741900; 2.338500;,
0.000500; 0.759800; 2.414600;,
0.090700; 0.759800; 2.414600;,
0.045600; 0.741900; 2.338500;,
0.000500; 0.759800; 2.414600;,
0.045600; 0.777700; 2.490700;,
0.090700; 0.759800; 2.414600;,
0.000500; 0.759800; 2.414600;,
-0.044700; 0.777700; 2.490700;,
0.045600; 0.777700; 2.490700;,
0.000500; 0.759800; 2.414600;,
-0.089800; 0.759800; 2.414600;,
-0.044700; 0.777700; 2.490700;,
0.000500; 0.759800; 2.414600;,
-0.044700; 0.741900; 2.338500;,
-0.089800; 0.759800; 2.414600;,
0.000500; 0.759800; 2.414600;,
0.045600; 0.741900; 2.338500;,
-0.044700; 0.741900; 2.338500;,
-0.016000; 0.534300; 2.405400;,
0.016900; 0.534300; 2.405400;,
0.000500; 0.562000; 2.398900;,
0.000500; 0.562000; 2.398900;,
-0.032400; 0.562000; 2.398900;,
-0.016000; 0.534300; 2.405400;,
0.000500; 0.562000; 2.398900;,
-0.016000; 0.589700; 2.392400;,
-0.032400; 0.562000; 2.398900;,
0.000500; 0.562000; 2.398900;,
0.016900; 0.589700; 2.392400;,
-0.016000; 0.589700; 2.392400;,
0.000500; 0.562000; 2.398900;,
0.033300; 0.562000; 2.398900;,
0.016900; 0.589700; 2.392400;,
0.000500; 0.562000; 2.398900;,
0.016900; 0.534300; 2.405400;,
0.033300; 0.562000; 2.398900;,
0.033300; 0.562000; 2.398900;,
0.016900; 0.534300; 2.405400;,
0.016900; 0.523500; 2.359500;,
0.033300; 0.551200; 2.353000;,
0.016900; 0.589700; 2.392400;,
0.033300; 0.562000; 2.398900;,
0.033300; 0.551200; 2.353000;,
0.016900; 0.578900; 2.346500;,
-0.016000; 0.589700; 2.392400;,
0.016900; 0.589700; 2.392400;,
0.016900; 0.578900; 2.346500;,
-0.016000; 0.578900; 2.346500;,
-0.032400; 0.562000; 2.398900;,
-0.016000; 0.589700; 2.392400;,
-0.016000; 0.578900; 2.346500;,
-0.032400; 0.551200; 2.353000;,
-0.016000; 0.534300; 2.405400;,
-0.032400; 0.562000; 2.398900;,
-0.032400; 0.551200; 2.353000;,
-0.016000; 0.523500; 2.359500;,
0.016900; 0.534300; 2.405400;,
-0.016000; 0.534300; 2.405400;,
-0.016000; 0.523500; 2.359500;,
0.016900; 0.523500; 2.359500;,
0.016900; 0.523500; 2.359500;,
-0.016000; 0.523500; 2.359500;,
-0.025100; 0.508200; 2.363100;,
0.026000; 0.508200; 2.363100;,
-0.016000; 0.523500; 2.359500;,
-0.032400; 0.551200; 2.353000;,
-0.050600; 0.551200; 2.353000;,
-0.025100; 0.508200; 2.363100;,
-0.032400; 0.551200; 2.353000;,
-0.016000; 0.578900; 2.346500;,
-0.025100; 0.594200; 2.342900;,
-0.050600; 0.551200; 2.353000;,
-0.016000; 0.578900; 2.346500;,
0.016900; 0.578900; 2.346500;,
0.026000; 0.594200; 2.342900;,
-0.025100; 0.594200; 2.342900;,
0.016900; 0.578900; 2.346500;,
0.033300; 0.551200; 2.353000;,
0.051500; 0.551200; 2.353000;,
0.026000; 0.594200; 2.342900;,
0.033300; 0.551200; 2.353000;,
0.016900; 0.523500; 2.359500;,
0.026000; 0.508200; 2.363100;,
0.051500; 0.551200; 2.353000;,
0.026000; 0.508200; 2.363100;,
-0.025100; 0.508200; 2.363100;,
-0.025100; 0.494300; 2.304100;,
0.026000; 0.494300; 2.304100;,
-0.025100; 0.508200; 2.363100;,
-0.050600; 0.551200; 2.353000;,
-0.050600; 0.537300; 2.294000;,
-0.025100; 0.494300; 2.304100;,
-0.050600; 0.551200; 2.353000;,
-0.025100; 0.594200; 2.342900;,
-0.025100; 0.580300; 2.283800;,
-0.050600; 0.537300; 2.294000;,
-0.025100; 0.594200; 2.342900;,
0.026000; 0.594200; 2.342900;,
0.026000; 0.580300; 2.283800;,
-0.025100; 0.580300; 2.283800;,
0.026000; 0.594200; 2.342900;,
0.051500; 0.551200; 2.353000;,
0.051500; 0.537300; 2.294000;,
0.026000; 0.580300; 2.283800;,
0.051500; 0.551200; 2.353000;,
0.026000; 0.508200; 2.363100;,
0.026000; 0.494300; 2.304100;,
0.051500; 0.537300; 2.294000;,
0.026000; 0.494300; 2.304100;,
-0.025100; 0.494300; 2.304100;,
-0.014700; 0.505800; 2.274100;,
0.015600; 0.505800; 2.274100;,
-0.025100; 0.494300; 2.304100;,
-0.050600; 0.537300; 2.294000;,
-0.029800; 0.531200; 2.268100;,
-0.014700; 0.505800; 2.274100;,
-0.050600; 0.537300; 2.294000;,
-0.025100; 0.580300; 2.283800;,
-0.014700; 0.556700; 2.262100;,
-0.029800; 0.531200; 2.268100;,
-0.025100; 0.580300; 2.283800;,
0.026000; 0.580300; 2.283800;,
0.015600; 0.556700; 2.262100;,
-0.014700; 0.556700; 2.262100;,
0.026000; 0.580300; 2.283800;,
0.051500; 0.537300; 2.294000;,
0.030700; 0.531200; 2.268100;,
0.015600; 0.556700; 2.262100;,
0.051500; 0.537300; 2.294000;,
0.026000; 0.494300; 2.304100;,
0.015600; 0.505800; 2.274100;,
0.030700; 0.531200; 2.268100;,
0.015600; 0.505800; 2.274100;,
-0.014700; 0.505800; 2.274100;,
0.000500; 0.531200; 2.268100;,
-0.014700; 0.505800; 2.274100;,
-0.029800; 0.531200; 2.268100;,
0.000500; 0.531200; 2.268100;,
-0.029800; 0.531200; 2.268100;,
-0.014700; 0.556700; 2.262100;,
0.000500; 0.531200; 2.268100;,
-0.014700; 0.556700; 2.262100;,
0.015600; 0.556700; 2.262100;,
0.000500; 0.531200; 2.268100;,
0.015600; 0.556700; 2.262100;,
0.030700; 0.531200; 2.268100;,
0.000500; 0.531200; 2.268100;,
0.030700; 0.531200; 2.268100;,
0.015600; 0.505800; 2.274100;,
0.000500; 0.531200; 2.268100;,
0.287400; 0.289100; 2.144000;,
0.406500; 0.001600; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.000100; 0.001600; 2.144000;,
0.406500; 0.001600; 2.144000;,
0.287400; -0.286000; 2.144000;,
-0.000100; 0.001600; 2.144000;,
0.287400; -0.286000; 2.144000;,
-0.000100; -0.405000; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.000100; -0.405000; 2.144000;,
-0.287500; -0.286000; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.287500; -0.286000; 2.144000;,
-0.406700; 0.001600; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.406700; 0.001600; 2.144000;,
-0.287500; 0.288900; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.287500; 0.288900; 2.144000;,
-0.000100; 0.408200; 2.144000;,
-0.000100; 0.001600; 2.144000;,
-0.000100; 0.408200; 2.144000;,
0.287400; 0.289100; 2.144000;,
0.287400; 0.289100; 2.144000;,
0.287400; 0.289100; 2.335700;,
0.406500; 0.001600; 2.335700;,
0.406500; 0.001600; 2.144000;,
0.406500; 0.001600; 2.144000;,
0.406500; 0.001600; 2.335700;,
0.287400; -0.286000; 2.335700;,
0.287400; -0.286000; 2.144000;,
0.287400; -0.286000; 2.144000;,
0.287400; -0.286000; 2.335700;,
-0.000100; -0.405000; 2.335700;,
-0.000100; -0.405000; 2.144000;,
-0.000100; -0.405000; 2.144000;,
-0.000100; -0.405000; 2.335700;,
-0.287500; -0.286000; 2.335700;,
-0.287500; -0.286000; 2.144000;,
-0.287500; -0.286000; 2.144000;,
-0.287500; -0.286000; 2.335700;,
-0.406700; 0.001600; 2.335700;,
-0.406700; 0.001600; 2.144000;,
-0.406700; 0.001600; 2.144000;,
-0.406700; 0.001600; 2.335700;,
-0.287500; 0.288900; 2.335700;,
-0.287500; 0.288900; 2.144000;,
-0.287500; 0.288900; 2.144000;,
-0.287500; 0.288900; 2.335700;,
-0.000100; 0.408200; 2.335700;,
-0.000100; 0.408200; 2.144000;,
-0.000100; 0.408200; 2.144000;,
-0.000100; 0.408200; 2.335700;,
0.287400; 0.289100; 2.335700;,
0.287400; 0.289100; 2.144000;,
-0.000100; 0.408200; 2.335700;,
-0.000100; 0.277000; 2.335700;,
0.194700; 0.196400; 2.335700;,
0.287400; 0.289100; 2.335700;,
-0.287500; 0.288900; 2.335700;,
-0.194800; 0.196200; 2.335700;,
-0.000100; 0.277000; 2.335700;,
-0.000100; 0.408200; 2.335700;,
-0.406700; 0.001600; 2.335700;,
-0.275500; 0.001600; 2.335700;,
-0.194800; 0.196200; 2.335700;,
-0.287500; 0.288900; 2.335700;,
-0.287500; -0.286000; 2.335700;,
-0.194800; -0.193200; 2.335700;,
-0.275500; 0.001600; 2.335700;,
-0.406700; 0.001600; 2.335700;,
-0.000100; -0.405000; 2.335700;,
-0.000100; -0.273800; 2.335700;,
-0.194800; -0.193200; 2.335700;,
-0.287500; -0.286000; 2.335700;,
0.287400; -0.286000; 2.335700;,
0.194700; -0.193200; 2.335700;,
-0.000100; -0.273800; 2.335700;,
-0.000100; -0.405000; 2.335700;,
0.406500; 0.001600; 2.335700;,
0.275300; 0.001600; 2.335700;,
0.194700; -0.193200; 2.335700;,
0.287400; -0.286000; 2.335700;,
0.287400; 0.289100; 2.335700;,
0.194700; 0.196400; 2.335700;,
0.275300; 0.001600; 2.335700;,
0.406500; 0.001600; 2.335700;,
-0.000100; 0.277000; 2.335700;,
-0.000100; 0.143800; 2.831400;,
0.100500; 0.102100; 2.831400;,
0.194700; 0.196400; 2.335700;,
-0.194800; 0.196200; 2.335700;,
-0.100600; 0.102100; 2.831400;,
-0.000100; 0.143800; 2.831400;,
-0.000100; 0.277000; 2.335700;,
-0.275500; 0.001600; 2.335700;,
-0.142300; 0.001600; 2.831400;,
-0.100600; 0.102100; 2.831400;,
-0.194800; 0.196200; 2.335700;,
-0.194800; -0.193200; 2.335700;,
-0.100600; -0.099000; 2.831400;,
-0.142300; 0.001600; 2.831400;,
-0.275500; 0.001600; 2.335700;,
-0.000100; -0.273800; 2.335700;,
-0.000100; -0.140600; 2.831400;,
-0.100600; -0.099000; 2.831400;,
-0.194800; -0.193200; 2.335700;,
0.194700; -0.193200; 2.335700;,
0.100500; -0.099000; 2.831400;,
-0.000100; -0.140600; 2.831400;,
-0.000100; -0.273800; 2.335700;,
0.275300; 0.001600; 2.335700;,
0.142100; 0.001600; 2.831400;,
0.100500; -0.099000; 2.831400;,
0.194700; -0.193200; 2.335700;,
0.194700; 0.196400; 2.335700;,
0.100500; 0.102100; 2.831400;,
0.142100; 0.001600; 2.831400;,
0.275300; 0.001600; 2.335700;,
-0.000100; 0.143800; 2.831400;,
-0.000100; 0.001600; 2.885500;,
0.100500; 0.102100; 2.831400;,
-0.100600; 0.102100; 2.831400;,
-0.000100; 0.001600; 2.885500;,
-0.000100; 0.143800; 2.831400;,
-0.142300; 0.001600; 2.831400;,
-0.000100; 0.001600; 2.885500;,
-0.100600; 0.102100; 2.831400;,
-0.100600; -0.099000; 2.831400;,
-0.000100; 0.001600; 2.885500;,
-0.142300; 0.001600; 2.831400;,
-0.000100; -0.140600; 2.831400;,
-0.000100; 0.001600; 2.885500;,
-0.100600; -0.099000; 2.831400;,
0.100500; -0.099000; 2.831400;,
-0.000100; 0.001600; 2.885500;,
-0.000100; -0.140600; 2.831400;,
0.142100; 0.001600; 2.831400;,
-0.000100; 0.001600; 2.885500;,
0.100500; -0.099000; 2.831400;,
0.100500; 0.102100; 2.831400;,
-0.000100; 0.001600; 2.885500;,
0.142100; 0.001600; 2.831400;;
115;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
4; 9, 12, 11, 10;,
4; 13, 16, 15, 14;,
4; 17, 20, 19, 18;,
4; 21, 24, 23, 22;,
4; 25, 28, 27, 26;,
4; 29, 32, 31, 30;,
4; 33, 36, 35, 34;,
4; 37, 40, 39, 38;,
4; 41, 44, 43, 42;,
4; 45, 48, 47, 46;,
4; 49, 52, 51, 50;,
4; 53, 56, 55, 54;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
4; 69, 72, 71, 70;,
4; 73, 76, 75, 74;,
4; 77, 80, 79, 78;,
4; 81, 84, 83, 82;,
4; 85, 88, 87, 86;,
4; 89, 92, 91, 90;,
4; 93, 96, 95, 94;,
4; 97, 100, 99, 98;,
4; 101, 104, 103, 102;,
4; 105, 108, 107, 106;,
4; 109, 112, 111, 110;,
4; 113, 116, 115, 114;,
4; 117, 120, 119, 118;,
4; 121, 124, 123, 122;,
4; 125, 128, 127, 126;,
3; 129, 131, 130;,
3; 132, 134, 133;,
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;,
3; 150, 152, 151;,
3; 153, 155, 154;,
3; 156, 158, 157;,
3; 159, 161, 160;,
3; 162, 164, 163;,
4; 165, 168, 167, 166;,
4; 169, 172, 171, 170;,
4; 173, 176, 175, 174;,
4; 177, 180, 179, 178;,
4; 181, 184, 183, 182;,
4; 185, 188, 187, 186;,
4; 189, 192, 191, 190;,
4; 193, 196, 195, 194;,
4; 197, 200, 199, 198;,
4; 201, 204, 203, 202;,
4; 205, 208, 207, 206;,
4; 209, 212, 211, 210;,
4; 213, 216, 215, 214;,
4; 217, 220, 219, 218;,
4; 221, 224, 223, 222;,
4; 225, 228, 227, 226;,
4; 229, 232, 231, 230;,
4; 233, 236, 235, 234;,
4; 237, 240, 239, 238;,
4; 241, 244, 243, 242;,
4; 245, 248, 247, 246;,
4; 249, 252, 251, 250;,
4; 253, 256, 255, 254;,
4; 257, 260, 259, 258;,
3; 261, 263, 262;,
3; 264, 266, 265;,
3; 267, 269, 268;,
3; 270, 272, 271;,
3; 273, 275, 274;,
3; 276, 278, 277;,
3; 279, 281, 280;,
3; 282, 284, 283;,
3; 285, 287, 286;,
3; 288, 290, 289;,
3; 291, 293, 292;,
3; 294, 296, 295;,
3; 297, 299, 298;,
3; 300, 302, 301;,
4; 303, 306, 305, 304;,
4; 307, 310, 309, 308;,
4; 311, 314, 313, 312;,
4; 315, 318, 317, 316;,
4; 319, 322, 321, 320;,
4; 323, 326, 325, 324;,
4; 327, 330, 329, 328;,
4; 331, 334, 333, 332;,
4; 335, 338, 337, 336;,
4; 339, 342, 341, 340;,
4; 343, 346, 345, 344;,
4; 347, 350, 349, 348;,
4; 351, 354, 353, 352;,
4; 355, 358, 357, 356;,
4; 359, 362, 361, 360;,
4; 363, 366, 365, 364;,
4; 367, 370, 369, 368;,
4; 371, 374, 373, 372;,
4; 375, 378, 377, 376;,
4; 379, 382, 381, 380;,
4; 383, 386, 385, 384;,
4; 387, 390, 389, 388;,
4; 391, 394, 393, 392;,
4; 395, 398, 397, 396;,
3; 399, 401, 400;,
3; 402, 404, 403;,
3; 405, 407, 406;,
3; 408, 410, 409;,
3; 411, 413, 412;,
3; 414, 416, 415;,
3; 417, 419, 418;,
3; 420, 422, 421;;
  MeshMaterialList {
    2;
    115;
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1;;
  Material Poison1 {
    0.000000; 0.900000; 0.200000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Poison1_Head {
    0.180671; 0.269823; 0.183432;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
423;
    0.000001; -0.973375; 0.229220;,
    0.000001; -0.973375; 0.229220;,
    0.000001; -0.973375; 0.229220;,
    0.000000; -0.973375; 0.229219;,
    0.000000; -0.973375; 0.229219;,
    0.000000; -0.973375; 0.229219;,
    0.000000; -0.973375; 0.229219;,
    0.000000; -0.973375; 0.229219;,
    0.000000; -0.973375; 0.229219;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    -0.866026; 0.114610; 0.486687;,
    -0.866026; 0.114610; 0.486687;,
    -0.866026; 0.114610; 0.486687;,
    -0.866026; 0.114610; 0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    0.000000; -0.229220; -0.973375;,
    0.000000; -0.229220; -0.973375;,
    0.000000; -0.229220; -0.973375;,
    0.000000; -0.229220; -0.973375;,
    0.000000; -0.973376; 0.229216;,
    0.000000; -0.973376; 0.229216;,
    0.000000; -0.973376; 0.229216;,
    0.000000; -0.973376; 0.229216;,
    -0.000002; -0.973374; 0.229221;,
    -0.000002; -0.973374; 0.229221;,
    -0.000002; -0.973374; 0.229221;,
    -0.000002; -0.973374; 0.229221;,
    -0.000001; -0.973374; 0.229225;,
    -0.000001; -0.973374; 0.229225;,
    -0.000001; -0.973374; 0.229225;,
    -0.000001; -0.973374; 0.229225;,
    0.000000; -0.973373; 0.229228;,
    0.000000; -0.973373; 0.229228;,
    0.000000; -0.973373; 0.229228;,
    0.000000; -0.973373; 0.229228;,
    0.000002; -0.973374; 0.229225;,
    0.000002; -0.973374; 0.229225;,
    0.000002; -0.973374; 0.229225;,
    0.000002; -0.973374; 0.229225;,
    0.000003; -0.973374; 0.229221;,
    0.000003; -0.973374; 0.229221;,
    0.000003; -0.973374; 0.229221;,
    0.000003; -0.973374; 0.229221;,
    0.866025; -0.114611; -0.486688;,
    0.866025; -0.114611; -0.486688;,
    0.866025; -0.114611; -0.486688;,
    0.866025; -0.114611; -0.486688;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.866026; 0.114610; 0.486687;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    0.000000; 0.229220; 0.973375;,
    -0.866025; 0.114610; 0.486688;,
    -0.866025; 0.114610; 0.486688;,
    -0.866025; 0.114610; 0.486688;,
    -0.866025; 0.114610; 0.486688;,
    -0.866026; -0.114610; -0.486686;,
    -0.866026; -0.114610; -0.486686;,
    -0.866026; -0.114610; -0.486686;,
    -0.866026; -0.114610; -0.486686;,
    0.000000; -0.229221; -0.973374;,
    0.000000; -0.229221; -0.973374;,
    0.000000; -0.229221; -0.973374;,
    0.000000; -0.229221; -0.973374;,
    0.000000; 0.973375; -0.229220;,
    0.000000; 0.973375; -0.229220;,
    0.000000; 0.973375; -0.229220;,
    0.000000; 0.973375; -0.229220;,
    0.000001; 0.973374; -0.229222;,
    0.000001; 0.973374; -0.229222;,
    0.000001; 0.973374; -0.229222;,
    0.000001; 0.973374; -0.229222;,
    0.000003; 0.973374; -0.229223;,
    0.000003; 0.973374; -0.229223;,
    0.000003; 0.973374; -0.229223;,
    0.000003; 0.973374; -0.229223;,
    0.000000; 0.973373; -0.229227;,
    0.000000; 0.973373; -0.229227;,
    0.000000; 0.973373; -0.229227;,
    0.000000; 0.973373; -0.229227;,
    -0.000003; 0.973374; -0.229222;,
    -0.000003; 0.973374; -0.229222;,
    -0.000003; 0.973374; -0.229222;,
    -0.000003; 0.973374; -0.229222;,
    -0.000001; 0.973374; -0.229222;,
    -0.000001; 0.973374; -0.229222;,
    -0.000001; 0.973374; -0.229222;,
    -0.000001; 0.973374; -0.229222;,
    -0.866025; 0.114610; 0.486687;,
    -0.866025; 0.114610; 0.486687;,
    -0.866025; 0.114610; 0.486687;,
    -0.866025; 0.114610; 0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    -0.866026; -0.114610; -0.486687;,
    0.000000; -0.229219; -0.973375;,
    0.000000; -0.229219; -0.973375;,
    0.000000; -0.229219; -0.973375;,
    0.000000; -0.229219; -0.973375;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866025; -0.114610; -0.486688;,
    0.866026; 0.114609; 0.486686;,
    0.866026; 0.114609; 0.486686;,
    0.866026; 0.114609; 0.486686;,
    0.866026; 0.114609; 0.486686;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229222;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.973374; -0.229221;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229228; 0.973373;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.000000; 0.229219; 0.973375;,
    0.866025; -0.486687; 0.114612;,
    0.866025; -0.486687; 0.114612;,
    0.866025; -0.486687; 0.114612;,
    0.866025; -0.486687; 0.114612;,
    0.866026; 0.486686; -0.114610;,
    0.866026; 0.486686; -0.114610;,
    0.866026; 0.486686; -0.114610;,
    0.866026; 0.486686; -0.114610;,
    0.000000; 0.973376; -0.229216;,
    0.000000; 0.973376; -0.229216;,
    0.000000; 0.973376; -0.229216;,
    0.000000; 0.973376; -0.229216;,
    -0.866026; 0.486686; -0.114610;,
    -0.866026; 0.486686; -0.114610;,
    -0.866026; 0.486686; -0.114610;,
    -0.866026; 0.486686; -0.114610;,
    -0.866025; -0.486687; 0.114612;,
    -0.866025; -0.486687; 0.114612;,
    -0.866025; -0.486687; 0.114612;,
    -0.866025; -0.486687; 0.114612;,
    0.000000; -0.973374; 0.229223;,
    0.000000; -0.973374; 0.229223;,
    0.000000; -0.973374; 0.229223;,
    0.000000; -0.973374; 0.229223;,
    0.000000; 0.229225; 0.973373;,
    0.000000; 0.229225; 0.973373;,
    0.000000; 0.229225; 0.973373;,
    0.000000; 0.229225; 0.973373;,
    0.000002; 0.229222; 0.973374;,
    0.000002; 0.229222; 0.973374;,
    0.000002; 0.229222; 0.973374;,
    0.000002; 0.229222; 0.973374;,
    0.000006; 0.229218; 0.973375;,
    0.000006; 0.229218; 0.973375;,
    0.000006; 0.229218; 0.973375;,
    0.000006; 0.229218; 0.973375;,
    0.000000; 0.229209; 0.973377;,
    0.000000; 0.229209; 0.973377;,
    0.000000; 0.229209; 0.973377;,
    0.000000; 0.229209; 0.973377;,
    -0.000006; 0.229218; 0.973375;,
    -0.000006; 0.229218; 0.973375;,
    -0.000006; 0.229218; 0.973375;,
    -0.000006; 0.229218; 0.973375;,
    -0.000002; 0.229222; 0.973374;,
    -0.000002; 0.229222; 0.973374;,
    -0.000002; 0.229222; 0.973374;,
    -0.000002; 0.229222; 0.973374;,
    0.000000; -0.973374; 0.229224;,
    0.000000; -0.973374; 0.229224;,
    0.000000; -0.973374; 0.229224;,
    0.000000; -0.973374; 0.229224;,
    -0.866026; -0.486687; 0.114611;,
    -0.866026; -0.486687; 0.114611;,
    -0.866026; -0.486687; 0.114611;,
    -0.866026; -0.486687; 0.114611;,
    -0.866027; 0.486685; -0.114611;,
    -0.866027; 0.486685; -0.114611;,
    -0.866027; 0.486685; -0.114611;,
    -0.866027; 0.486685; -0.114611;,
    -0.000002; 0.973374; -0.229223;,
    -0.000002; 0.973374; -0.229223;,
    -0.000002; 0.973374; -0.229223;,
    -0.000002; 0.973374; -0.229223;,
    0.866027; 0.486685; -0.114610;,
    0.866027; 0.486685; -0.114610;,
    0.866027; 0.486685; -0.114610;,
    0.866027; 0.486685; -0.114610;,
    0.866025; -0.486687; 0.114611;,
    0.866025; -0.486687; 0.114611;,
    0.866025; -0.486687; 0.114611;,
    0.866025; -0.486687; 0.114611;,
    0.000000; -0.933915; -0.357496;,
    0.000000; -0.933915; -0.357496;,
    0.000000; -0.933915; -0.357496;,
    0.000000; -0.933915; -0.357496;,
    -0.716295; -0.531371; -0.452290;,
    -0.716295; -0.531371; -0.452290;,
    -0.716295; -0.531371; -0.452290;,
    -0.716295; -0.531371; -0.452290;,
    -0.716297; 0.273705; -0.641876;,
    -0.716297; 0.273705; -0.641876;,
    -0.716297; 0.273705; -0.641876;,
    -0.716297; 0.273705; -0.641876;,
    -0.000002; 0.676249; -0.736673;,
    -0.000002; 0.676249; -0.736673;,
    -0.000002; 0.676249; -0.736673;,
    -0.000002; 0.676249; -0.736673;,
    0.716297; 0.273705; -0.641876;,
    0.716297; 0.273705; -0.641876;,
    0.716297; 0.273705; -0.641876;,
    0.716297; 0.273705; -0.641876;,
    0.716294; -0.531371; -0.452291;,
    0.716294; -0.531371; -0.452291;,
    0.716294; -0.531371; -0.452291;,
    0.716294; -0.531371; -0.452291;,
    0.000000; -0.229218; -0.973375;,
    0.000000; -0.229218; -0.973375;,
    0.000000; -0.229218; -0.973375;,
    0.000001; -0.229219; -0.973375;,
    0.000001; -0.229219; -0.973375;,
    0.000001; -0.229219; -0.973375;,
    0.000001; -0.229229; -0.973373;,
    0.000001; -0.229229; -0.973373;,
    0.000001; -0.229229; -0.973373;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229229; -0.973372;,
    0.000000; -0.229218; -0.973375;,
    0.000000; -0.229218; -0.973375;,
    0.000000; -0.229218; -0.973375;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.000000; 0.000000; -1.000000;,
    0.923965; 0.382478; 0.000000;,
    0.923965; 0.382478; 0.000000;,
    0.923965; 0.382478; 0.000000;,
    0.923965; 0.382478; 0.000000;,
    0.923965; -0.382478; 0.000000;,
    0.923965; -0.382478; 0.000000;,
    0.923965; -0.382478; 0.000000;,
    0.923965; -0.382478; 0.000000;,
    0.382478; -0.923964; 0.000000;,
    0.382478; -0.923964; 0.000000;,
    0.382478; -0.923964; 0.000000;,
    0.382478; -0.923964; 0.000000;,
    -0.382696; -0.923874; 0.000000;,
    -0.382696; -0.923874; 0.000000;,
    -0.382696; -0.923874; 0.000000;,
    -0.382696; -0.923874; 0.000000;,
    -0.923747; -0.383002; 0.000000;,
    -0.923747; -0.383002; 0.000000;,
    -0.923747; -0.383002; 0.000000;,
    -0.923747; -0.383002; 0.000000;,
    -0.923657; 0.383219; 0.000000;,
    -0.923657; 0.383219; 0.000000;,
    -0.923657; 0.383219; 0.000000;,
    -0.923657; 0.383219; 0.000000;,
    -0.383219; 0.923657; 0.000000;,
    -0.383219; 0.923657; 0.000000;,
    -0.383219; 0.923657; 0.000000;,
    -0.383219; 0.923657; 0.000000;,
    0.382478; 0.923965; 0.000000;,
    0.382478; 0.923965; 0.000000;,
    0.382478; 0.923965; 0.000000;,
    0.382478; 0.923965; 0.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.371201; 0.896723; 0.241034;,
    0.371201; 0.896723; 0.241034;,
    0.371201; 0.896723; 0.241034;,
    0.371201; 0.896723; 0.241034;,
    -0.371928; 0.896441; 0.240965;,
    -0.371928; 0.896441; 0.240965;,
    -0.371928; 0.896441; 0.240965;,
    -0.371928; 0.896441; 0.240965;,
    -0.896440; 0.371927; 0.240968;,
    -0.896440; 0.371927; 0.240968;,
    -0.896440; 0.371927; 0.240968;,
    -0.896440; 0.371927; 0.240968;,
    -0.896523; -0.371714; 0.240989;,
    -0.896523; -0.371714; 0.240989;,
    -0.896523; -0.371714; 0.240989;,
    -0.896523; -0.371714; 0.240989;,
    -0.371414; -0.896640; 0.241015;,
    -0.371414; -0.896640; 0.241015;,
    -0.371414; -0.896640; 0.241015;,
    -0.371414; -0.896640; 0.241015;,
    0.371202; -0.896724; 0.241031;,
    0.371202; -0.896724; 0.241031;,
    0.371202; -0.896724; 0.241031;,
    0.371202; -0.896724; 0.241031;,
    0.896724; -0.371202; 0.241027;,
    0.896724; -0.371202; 0.241027;,
    0.896724; -0.371202; 0.241027;,
    0.896724; -0.371202; 0.241027;,
    0.896724; 0.371202; 0.241029;,
    0.896724; 0.371202; 0.241029;,
    0.896724; 0.371202; 0.241029;,
    0.896724; 0.371202; 0.241029;,
    0.145536; 0.351576; 0.924778;,
    0.145536; 0.351576; 0.924778;,
    0.145536; 0.351576; 0.924778;,
    -0.145860; 0.351559; 0.924733;,
    -0.145860; 0.351559; 0.924733;,
    -0.145860; 0.351559; 0.924733;,
    -0.351559; 0.145860; 0.924733;,
    -0.351559; 0.145860; 0.924733;,
    -0.351559; 0.145860; 0.924733;,
    -0.351564; -0.145765; 0.924746;,
    -0.351564; -0.145765; 0.924746;,
    -0.351564; -0.145765; 0.924746;,
    -0.145631; -0.351571; 0.924765;,
    -0.145631; -0.351571; 0.924765;,
    -0.145631; -0.351571; 0.924765;,
    0.145536; -0.351576; 0.924778;,
    0.145536; -0.351576; 0.924778;,
    0.145536; -0.351576; 0.924778;,
    0.351576; -0.145536; 0.924778;,
    0.351576; -0.145536; 0.924778;,
    0.351576; -0.145536; 0.924778;,
    0.351576; 0.145536; 0.924778;,
    0.351576; 0.145536; 0.924778;,
    0.351576; 0.145536; 0.924778;;
115;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
4; 9, 12, 11, 10;,
4; 13, 16, 15, 14;,
4; 17, 20, 19, 18;,
4; 21, 24, 23, 22;,
4; 25, 28, 27, 26;,
4; 29, 32, 31, 30;,
4; 33, 36, 35, 34;,
4; 37, 40, 39, 38;,
4; 41, 44, 43, 42;,
4; 45, 48, 47, 46;,
4; 49, 52, 51, 50;,
4; 53, 56, 55, 54;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
4; 69, 72, 71, 70;,
4; 73, 76, 75, 74;,
4; 77, 80, 79, 78;,
4; 81, 84, 83, 82;,
4; 85, 88, 87, 86;,
4; 89, 92, 91, 90;,
4; 93, 96, 95, 94;,
4; 97, 100, 99, 98;,
4; 101, 104, 103, 102;,
4; 105, 108, 107, 106;,
4; 109, 112, 111, 110;,
4; 113, 116, 115, 114;,
4; 117, 120, 119, 118;,
4; 121, 124, 123, 122;,
4; 125, 128, 127, 126;,
3; 129, 131, 130;,
3; 132, 134, 133;,
3; 135, 137, 136;,
3; 138, 140, 139;,
3; 141, 143, 142;,
3; 144, 146, 145;,
3; 147, 149, 148;,
3; 150, 152, 151;,
3; 153, 155, 154;,
3; 156, 158, 157;,
3; 159, 161, 160;,
3; 162, 164, 163;,
4; 165, 168, 167, 166;,
4; 169, 172, 171, 170;,
4; 173, 176, 175, 174;,
4; 177, 180, 179, 178;,
4; 181, 184, 183, 182;,
4; 185, 188, 187, 186;,
4; 189, 192, 191, 190;,
4; 193, 196, 195, 194;,
4; 197, 200, 199, 198;,
4; 201, 204, 203, 202;,
4; 205, 208, 207, 206;,
4; 209, 212, 211, 210;,
4; 213, 216, 215, 214;,
4; 217, 220, 219, 218;,
4; 221, 224, 223, 222;,
4; 225, 228, 227, 226;,
4; 229, 232, 231, 230;,
4; 233, 236, 235, 234;,
4; 237, 240, 239, 238;,
4; 241, 244, 243, 242;,
4; 245, 248, 247, 246;,
4; 249, 252, 251, 250;,
4; 253, 256, 255, 254;,
4; 257, 260, 259, 258;,
3; 261, 263, 262;,
3; 264, 266, 265;,
3; 267, 269, 268;,
3; 270, 272, 271;,
3; 273, 275, 274;,
3; 276, 278, 277;,
3; 279, 281, 280;,
3; 282, 284, 283;,
3; 285, 287, 286;,
3; 288, 290, 289;,
3; 291, 293, 292;,
3; 294, 296, 295;,
3; 297, 299, 298;,
3; 300, 302, 301;,
4; 303, 306, 305, 304;,
4; 307, 310, 309, 308;,
4; 311, 314, 313, 312;,
4; 315, 318, 317, 316;,
4; 319, 322, 321, 320;,
4; 323, 326, 325, 324;,
4; 327, 330, 329, 328;,
4; 331, 334, 333, 332;,
4; 335, 338, 337, 336;,
4; 339, 342, 341, 340;,
4; 343, 346, 345, 344;,
4; 347, 350, 349, 348;,
4; 351, 354, 353, 352;,
4; 355, 358, 357, 356;,
4; 359, 362, 361, 360;,
4; 363, 366, 365, 364;,
4; 367, 370, 369, 368;,
4; 371, 374, 373, 372;,
4; 375, 378, 377, 376;,
4; 379, 382, 381, 380;,
4; 383, 386, 385, 384;,
4; 387, 390, 389, 388;,
4; 391, 394, 393, 392;,
4; 395, 398, 397, 396;,
3; 399, 401, 400;,
3; 402, 404, 403;,
3; 405, 407, 406;,
3; 408, 410, 409;,
3; 411, 413, 412;,
3; 414, 416, 415;,
3; 417, 419, 418;,
3; 420, 422, 421;;
}  //End of MeshNormals
 }
}
}
