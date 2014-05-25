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
Frame Mesh_004 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
90;
-0.000000; -0.000000; -0.062700;,
0.011400; 0.035100; -0.050800;,
0.036900; -0.000000; -0.050800;,
0.036900; -0.000000; -0.050800;,
0.011400; 0.035100; -0.050800;,
0.018400; 0.056700; -0.019400;,
0.059700; -0.000000; -0.019400;,
0.059700; -0.000000; -0.019400;,
0.018400; 0.056700; -0.019400;,
0.018400; 0.056700; 0.019400;,
0.059700; -0.000000; 0.019400;,
0.011400; 0.035100; 0.050800;,
0.036900; -0.000000; 0.050800;,
0.059700; -0.000000; 0.019400;,
0.018400; 0.056700; 0.019400;,
0.036900; -0.000000; 0.050800;,
0.011400; 0.035100; 0.050800;,
-0.000000; -0.000000; 0.062700;,
0.011400; 0.035100; 0.050800;,
-0.029800; 0.021700; 0.050800;,
-0.000000; -0.000000; 0.062700;,
0.018400; 0.056700; 0.019400;,
-0.048300; 0.035100; 0.019400;,
-0.029800; 0.021700; 0.050800;,
0.011400; 0.035100; 0.050800;,
0.018400; 0.056700; -0.019400;,
-0.048300; 0.035100; -0.019400;,
-0.048300; 0.035100; 0.019400;,
0.018400; 0.056700; 0.019400;,
0.011400; 0.035100; -0.050800;,
-0.029800; 0.021700; -0.050800;,
-0.048300; 0.035100; -0.019400;,
0.018400; 0.056700; -0.019400;,
-0.029800; 0.021700; -0.050800;,
0.011400; 0.035100; -0.050800;,
-0.000000; -0.000000; -0.062700;,
-0.000000; -0.000000; -0.062700;,
-0.029800; -0.021700; -0.050800;,
-0.029800; 0.021700; -0.050800;,
-0.029800; 0.021700; -0.050800;,
-0.029800; -0.021700; -0.050800;,
-0.048300; -0.035100; -0.019400;,
-0.048300; 0.035100; -0.019400;,
-0.048300; 0.035100; -0.019400;,
-0.048300; -0.035100; -0.019400;,
-0.048300; -0.035100; 0.019400;,
-0.048300; 0.035100; 0.019400;,
-0.048300; 0.035100; 0.019400;,
-0.048300; -0.035100; 0.019400;,
-0.029800; -0.021700; 0.050800;,
-0.029800; 0.021700; 0.050800;,
-0.029800; 0.021700; 0.050800;,
-0.029800; -0.021700; 0.050800;,
-0.000000; -0.000000; 0.062700;,
-0.029800; -0.021700; 0.050800;,
0.011400; -0.035100; 0.050800;,
-0.000000; -0.000000; 0.062700;,
-0.048300; -0.035100; 0.019400;,
0.018400; -0.056700; 0.019400;,
0.011400; -0.035100; 0.050800;,
-0.029800; -0.021700; 0.050800;,
-0.048300; -0.035100; -0.019400;,
0.018400; -0.056700; -0.019400;,
0.018400; -0.056700; 0.019400;,
-0.048300; -0.035100; 0.019400;,
-0.029800; -0.021700; -0.050800;,
0.011400; -0.035100; -0.050800;,
0.018400; -0.056700; -0.019400;,
-0.048300; -0.035100; -0.019400;,
-0.000000; -0.000000; -0.062700;,
0.011400; -0.035100; -0.050800;,
-0.029800; -0.021700; -0.050800;,
-0.000000; -0.000000; -0.062700;,
0.036900; -0.000000; -0.050800;,
0.011400; -0.035100; -0.050800;,
0.011400; -0.035100; -0.050800;,
0.036900; -0.000000; -0.050800;,
0.059700; -0.000000; -0.019400;,
0.018400; -0.056700; -0.019400;,
0.018400; -0.056700; -0.019400;,
0.059700; -0.000000; -0.019400;,
0.059700; -0.000000; 0.019400;,
0.018400; -0.056700; 0.019400;,
0.036900; -0.000000; 0.050800;,
0.011400; -0.035100; 0.050800;,
0.018400; -0.056700; 0.019400;,
0.059700; -0.000000; 0.019400;,
0.011400; -0.035100; 0.050800;,
0.036900; -0.000000; 0.050800;,
-0.000000; -0.000000; 0.062700;;
25;
3; 0, 2, 1;,
4; 3, 6, 5, 4;,
4; 7, 10, 9, 8;,
4; 11, 14, 13, 12;,
3; 15, 17, 16;,
3; 18, 20, 19;,
4; 21, 24, 23, 22;,
4; 25, 28, 27, 26;,
4; 29, 32, 31, 30;,
3; 33, 35, 34;,
3; 36, 38, 37;,
4; 39, 42, 41, 40;,
4; 43, 46, 45, 44;,
4; 47, 50, 49, 48;,
3; 51, 53, 52;,
3; 54, 56, 55;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
3; 69, 71, 70;,
3; 72, 74, 73;,
4; 75, 78, 77, 76;,
4; 79, 82, 81, 80;,
4; 83, 86, 85, 84;,
3; 87, 89, 88;;
  MeshMaterialList {
    1;
    25;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;;
  Material Material_014 {
    0.041815; 0.327416; 1.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
90;
    0.301545; 0.219035; -0.927952;,
    0.301545; 0.219035; -0.927952;,
    0.301545; 0.219035; -0.927952;,
    0.697489; 0.506711; -0.506708;,
    0.697489; 0.506711; -0.506708;,
    0.697489; 0.506711; -0.506708;,
    0.697489; 0.506711; -0.506708;,
    0.809017; 0.587786; 0.000000;,
    0.809017; 0.587786; 0.000000;,
    0.809017; 0.587786; 0.000000;,
    0.809017; 0.587786; 0.000000;,
    0.697489; 0.506711; 0.506708;,
    0.697489; 0.506711; 0.506708;,
    0.697489; 0.506711; 0.506708;,
    0.697489; 0.506711; 0.506708;,
    0.301545; 0.219035; 0.927952;,
    0.301545; 0.219035; 0.927952;,
    0.301545; 0.219035; 0.927952;,
    -0.115154; 0.354508; 0.927935;,
    -0.115154; 0.354508; 0.927935;,
    -0.115154; 0.354508; 0.927935;,
    -0.266338; 0.819887; 0.506803;,
    -0.266338; 0.819887; 0.506803;,
    -0.266338; 0.819887; 0.506803;,
    -0.266338; 0.819887; 0.506803;,
    -0.308965; 0.951074; 0.000000;,
    -0.308965; 0.951074; 0.000000;,
    -0.308965; 0.951074; 0.000000;,
    -0.308965; 0.951074; 0.000000;,
    -0.266338; 0.819887; -0.506803;,
    -0.266338; 0.819887; -0.506803;,
    -0.266338; 0.819887; -0.506803;,
    -0.266338; 0.819887; -0.506803;,
    -0.115154; 0.354508; -0.927935;,
    -0.115154; 0.354508; -0.927935;,
    -0.115154; 0.354508; -0.927935;,
    -0.372654; 0.000000; -0.927970;,
    -0.372654; 0.000000; -0.927970;,
    -0.372654; 0.000000; -0.927970;,
    -0.862067; 0.000000; -0.506794;,
    -0.862067; 0.000000; -0.506794;,
    -0.862067; 0.000000; -0.506794;,
    -0.862067; 0.000000; -0.506794;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -1.000000; 0.000000; 0.000000;,
    -0.862067; 0.000000; 0.506794;,
    -0.862067; 0.000000; 0.506794;,
    -0.862067; 0.000000; 0.506794;,
    -0.862067; 0.000000; 0.506794;,
    -0.372654; 0.000000; 0.927970;,
    -0.372654; 0.000000; 0.927970;,
    -0.372654; 0.000000; 0.927970;,
    -0.115154; -0.354508; 0.927935;,
    -0.115154; -0.354508; 0.927935;,
    -0.115154; -0.354508; 0.927935;,
    -0.266338; -0.819887; 0.506803;,
    -0.266338; -0.819887; 0.506803;,
    -0.266338; -0.819887; 0.506803;,
    -0.266338; -0.819887; 0.506803;,
    -0.308965; -0.951074; 0.000000;,
    -0.308965; -0.951074; 0.000000;,
    -0.308965; -0.951074; 0.000000;,
    -0.308965; -0.951074; 0.000000;,
    -0.266338; -0.819887; -0.506803;,
    -0.266338; -0.819887; -0.506803;,
    -0.266338; -0.819887; -0.506803;,
    -0.266338; -0.819887; -0.506803;,
    -0.115154; -0.354508; -0.927935;,
    -0.115154; -0.354508; -0.927935;,
    -0.115154; -0.354508; -0.927935;,
    0.301545; -0.219035; -0.927952;,
    0.301545; -0.219035; -0.927952;,
    0.301545; -0.219035; -0.927952;,
    0.697489; -0.506711; -0.506708;,
    0.697489; -0.506711; -0.506708;,
    0.697489; -0.506711; -0.506708;,
    0.697489; -0.506711; -0.506708;,
    0.809017; -0.587786; 0.000000;,
    0.809017; -0.587786; 0.000000;,
    0.809017; -0.587786; 0.000000;,
    0.809017; -0.587786; 0.000000;,
    0.697489; -0.506711; 0.506708;,
    0.697489; -0.506711; 0.506708;,
    0.697489; -0.506711; 0.506708;,
    0.697489; -0.506711; 0.506708;,
    0.301545; -0.219035; 0.927952;,
    0.301545; -0.219035; 0.927952;,
    0.301545; -0.219035; 0.927952;;
25;
3; 0, 2, 1;,
4; 3, 6, 5, 4;,
4; 7, 10, 9, 8;,
4; 11, 14, 13, 12;,
3; 15, 17, 16;,
3; 18, 20, 19;,
4; 21, 24, 23, 22;,
4; 25, 28, 27, 26;,
4; 29, 32, 31, 30;,
3; 33, 35, 34;,
3; 36, 38, 37;,
4; 39, 42, 41, 40;,
4; 43, 46, 45, 44;,
4; 47, 50, 49, 48;,
3; 51, 53, 52;,
3; 54, 56, 55;,
4; 57, 60, 59, 58;,
4; 61, 64, 63, 62;,
4; 65, 68, 67, 66;,
3; 69, 71, 70;,
3; 72, 74, 73;,
4; 75, 78, 77, 76;,
4; 79, 82, 81, 80;,
4; 83, 86, 85, 84;,
3; 87, 89, 88;;
}  //End of MeshNormals
 }
}
}