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
Frame Mesh_001 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
64;
-1.000000; 0.950000; 0.000000;,
-0.950000; 0.950000; 0.000000;,
-0.950000; 1.000000; 0.000000;,
-1.000000; 1.000000; 0.000000;,
-0.950000; 0.950000; 0.000000;,
0.000000; 0.950000; 0.000000;,
0.000000; 1.000000; 0.000000;,
-0.950000; 1.000000; 0.000000;,
-0.950000; 0.950000; 0.000000;,
-1.000000; 0.950000; 0.000000;,
-1.000000; 0.000000; 0.000000;,
-0.950000; 0.000000; 0.000000;,
0.000000; 0.950000; 0.000000;,
-0.950000; 0.950000; 0.000000;,
-0.950000; 0.000000; 0.000000;,
0.000000; 0.000000; 0.000000;,
0.950000; 1.000000; 0.000000;,
0.000000; 1.000000; 0.000000;,
0.000000; 0.950000; 0.000000;,
0.950000; 0.950000; 0.000000;,
1.000000; 1.000000; 0.000000;,
0.950000; 1.000000; 0.000000;,
0.950000; 0.950000; 0.000000;,
1.000000; 0.950000; 0.000000;,
0.950000; 0.950000; 0.000000;,
0.000000; 0.950000; 0.000000;,
0.000000; 0.000000; 0.000000;,
0.950000; 0.000000; 0.000000;,
1.000000; 0.950000; 0.000000;,
0.950000; 0.950000; 0.000000;,
0.950000; 0.000000; 0.000000;,
1.000000; 0.000000; 0.000000;,
-0.950000; 0.000000; 0.000000;,
-1.000000; 0.000000; 0.000000;,
-1.000000; -0.950000; 0.000000;,
-0.950000; -0.950000; 0.000000;,
0.000000; 0.000000; 0.000000;,
-0.950000; 0.000000; 0.000000;,
-0.950000; -0.950000; 0.000000;,
0.000000; -0.950000; 0.000000;,
-0.950000; -0.950000; 0.000000;,
-1.000000; -0.950000; 0.000000;,
-1.000000; -1.000000; 0.000000;,
-0.950000; -1.000000; 0.000000;,
0.000000; -0.950000; 0.000000;,
-0.950000; -0.950000; 0.000000;,
-0.950000; -1.000000; 0.000000;,
0.000000; -1.000000; 0.000000;,
0.950000; 0.000000; 0.000000;,
0.000000; 0.000000; 0.000000;,
0.000000; -0.950000; 0.000000;,
0.950000; -0.950000; 0.000000;,
1.000000; 0.000000; 0.000000;,
0.950000; 0.000000; 0.000000;,
0.950000; -0.950000; 0.000000;,
1.000000; -0.950000; 0.000000;,
0.950000; -0.950000; 0.000000;,
0.000000; -0.950000; 0.000000;,
0.000000; -1.000000; 0.000000;,
0.950000; -1.000000; 0.000000;,
1.000000; -0.950000; 0.000000;,
0.950000; -0.950000; 0.000000;,
0.950000; -1.000000; 0.000000;,
1.000000; -1.000000; 0.000000;;
16;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;;
  MeshMaterialList {
    5;
    16;
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4,
    4;;
  Material Material_003 {
    0.800000; 0.800000; 0.800000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Material_004 {
    0.000000; 0.000000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Material_005 {
    0.914284; 0.742851; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Material_006 {
    1.000000; 1.000000; 1.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
  Material Material_007 {
    0.000000; 1.000000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
64;
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
    0.000000; 0.000000; 1.000000;;
16;
4; 0, 3, 2, 1;,
4; 4, 7, 6, 5;,
4; 8, 11, 10, 9;,
4; 12, 15, 14, 13;,
4; 16, 19, 18, 17;,
4; 20, 23, 22, 21;,
4; 24, 27, 26, 25;,
4; 28, 31, 30, 29;,
4; 32, 35, 34, 33;,
4; 36, 39, 38, 37;,
4; 40, 43, 42, 41;,
4; 44, 47, 46, 45;,
4; 48, 51, 50, 49;,
4; 52, 55, 54, 53;,
4; 56, 59, 58, 57;,
4; 60, 63, 62, 61;;
}  //End of MeshNormals
 }
}
}
