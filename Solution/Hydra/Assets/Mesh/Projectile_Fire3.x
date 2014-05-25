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
Frame Sphere_002 {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
Mesh {
60;
-0.047300; -0.145600; -0.076600;,
0.000000; 0.000000; -0.171200;,
0.123900; -0.090000; -0.076600;,
0.123900; -0.090000; -0.076600;,
0.000000; 0.000000; -0.171200;,
0.123900; 0.090000; -0.076600;,
-0.153100; 0.000000; -0.076600;,
0.000000; 0.000000; -0.171200;,
-0.047300; -0.145600; -0.076600;,
-0.047300; 0.145600; -0.076600;,
0.000000; 0.000000; -0.171200;,
-0.153100; 0.000000; -0.076600;,
0.123900; 0.090000; -0.076600;,
0.000000; 0.000000; -0.171200;,
-0.047300; 0.145600; -0.076600;,
0.123900; -0.090000; -0.076600;,
0.123900; 0.090000; -0.076600;,
0.153100; 0.000000; 0.076600;,
-0.047300; -0.145600; -0.076600;,
0.123900; -0.090000; -0.076600;,
0.047300; -0.145600; 0.076600;,
-0.153100; 0.000000; -0.076600;,
-0.047300; -0.145600; -0.076600;,
-0.123900; -0.090000; 0.076600;,
-0.047300; 0.145600; -0.076600;,
-0.153100; 0.000000; -0.076600;,
-0.123900; 0.090000; 0.076600;,
0.123900; 0.090000; -0.076600;,
-0.047300; 0.145600; -0.076600;,
0.047300; 0.145600; 0.076600;,
0.153100; 0.000000; 0.076600;,
0.047300; -0.145600; 0.076600;,
0.123900; -0.090000; -0.076600;,
0.047300; -0.145600; 0.076600;,
-0.123900; -0.090000; 0.076600;,
-0.047300; -0.145600; -0.076600;,
-0.123900; -0.090000; 0.076600;,
-0.123900; 0.090000; 0.076600;,
-0.153100; 0.000000; -0.076600;,
-0.123900; 0.090000; 0.076600;,
0.047300; 0.145600; 0.076600;,
-0.047300; 0.145600; -0.076600;,
0.047300; 0.145600; 0.076600;,
0.153100; 0.000000; 0.076600;,
0.123900; 0.090000; -0.076600;,
0.047300; -0.145600; 0.076600;,
0.153100; 0.000000; 0.076600;,
0.000000; 0.000000; 0.171200;,
-0.123900; -0.090000; 0.076600;,
0.047300; -0.145600; 0.076600;,
0.000000; 0.000000; 0.171200;,
-0.123900; 0.090000; 0.076600;,
-0.123900; -0.090000; 0.076600;,
0.000000; 0.000000; 0.171200;,
0.047300; 0.145600; 0.076600;,
-0.123900; 0.090000; 0.076600;,
0.000000; 0.000000; 0.171200;,
0.153100; 0.000000; 0.076600;,
0.047300; 0.145600; 0.076600;,
0.000000; 0.000000; 0.171200;;
20;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
3; 42, 44, 43;,
3; 45, 47, 46;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;;
  MeshMaterialList {
    1;
    20;
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
  Material FireBall {
    1.000000; 0.500000; 0.000000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
60;
    0.187597; -0.577354; -0.794651;,
    0.187597; -0.577354; -0.794651;,
    0.187597; -0.577354; -0.794651;,
    0.607065; 0.000000; -0.794652;,
    0.607065; 0.000000; -0.794652;,
    0.607065; 0.000000; -0.794652;,
    -0.491122; -0.356829; -0.794652;,
    -0.491122; -0.356829; -0.794652;,
    -0.491122; -0.356829; -0.794652;,
    -0.491122; 0.356829; -0.794652;,
    -0.491122; 0.356829; -0.794652;,
    -0.491122; 0.356829; -0.794652;,
    0.187597; 0.577354; -0.794651;,
    0.187597; 0.577354; -0.794651;,
    0.187597; 0.577354; -0.794651;,
    0.982246; 0.000000; -0.187597;,
    0.982246; 0.000000; -0.187597;,
    0.982246; 0.000000; -0.187597;,
    0.303536; -0.934171; -0.187589;,
    0.303536; -0.934171; -0.187589;,
    0.303536; -0.934171; -0.187589;,
    -0.794649; -0.577359; -0.187587;,
    -0.794649; -0.577359; -0.187587;,
    -0.794649; -0.577359; -0.187587;,
    -0.794649; 0.577359; -0.187587;,
    -0.794649; 0.577359; -0.187587;,
    -0.794649; 0.577359; -0.187587;,
    0.303536; 0.934171; -0.187589;,
    0.303536; 0.934171; -0.187589;,
    0.303536; 0.934171; -0.187589;,
    0.794649; -0.577359; 0.187587;,
    0.794649; -0.577359; 0.187587;,
    0.794649; -0.577359; 0.187587;,
    -0.303536; -0.934171; 0.187589;,
    -0.303536; -0.934171; 0.187589;,
    -0.303536; -0.934171; 0.187589;,
    -0.982246; 0.000000; 0.187597;,
    -0.982246; 0.000000; 0.187597;,
    -0.982246; 0.000000; 0.187597;,
    -0.303536; 0.934171; 0.187589;,
    -0.303536; 0.934171; 0.187589;,
    -0.303536; 0.934171; 0.187589;,
    0.794649; 0.577359; 0.187587;,
    0.794649; 0.577359; 0.187587;,
    0.794649; 0.577359; 0.187587;,
    0.491122; -0.356829; 0.794652;,
    0.491122; -0.356829; 0.794652;,
    0.491122; -0.356829; 0.794652;,
    -0.187597; -0.577354; 0.794651;,
    -0.187597; -0.577354; 0.794651;,
    -0.187597; -0.577354; 0.794651;,
    -0.607065; 0.000000; 0.794652;,
    -0.607065; 0.000000; 0.794652;,
    -0.607065; 0.000000; 0.794652;,
    -0.187597; 0.577354; 0.794651;,
    -0.187597; 0.577354; 0.794651;,
    -0.187597; 0.577354; 0.794651;,
    0.491122; 0.356829; 0.794652;,
    0.491122; 0.356829; 0.794652;,
    0.491122; 0.356829; 0.794652;;
20;
3; 0, 2, 1;,
3; 3, 5, 4;,
3; 6, 8, 7;,
3; 9, 11, 10;,
3; 12, 14, 13;,
3; 15, 17, 16;,
3; 18, 20, 19;,
3; 21, 23, 22;,
3; 24, 26, 25;,
3; 27, 29, 28;,
3; 30, 32, 31;,
3; 33, 35, 34;,
3; 36, 38, 37;,
3; 39, 41, 40;,
3; 42, 44, 43;,
3; 45, 47, 46;,
3; 48, 50, 49;,
3; 51, 53, 52;,
3; 54, 56, 55;,
3; 57, 59, 58;;
}  //End of MeshNormals
 }
}
}