xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 66;
 7.54370;0.02946;-2.00000;,
 7.54370;-0.73590;-1.84776;,
 0.04370;-0.73590;-1.84776;,
 0.04370;0.02946;-2.00000;,
 7.54370;-1.38475;-1.41421;,
 0.04370;-1.38475;-1.41421;,
 7.54370;-1.81829;-0.76537;,
 0.04370;-1.81829;-0.76537;,
 7.54370;-1.97054;-0.00000;,
 0.04370;-1.97054;-0.00000;,
 7.54370;-1.81829;0.76537;,
 0.04370;-1.81829;0.76537;,
 7.54370;-1.38475;1.41421;,
 0.04370;-1.38475;1.41421;,
 7.54370;-0.73590;1.84776;,
 0.04370;-0.73590;1.84776;,
 7.54370;0.02946;2.00000;,
 0.04370;0.02946;2.00000;,
 7.54370;0.79483;1.84776;,
 0.04370;0.79483;1.84776;,
 7.54370;1.44368;1.41421;,
 0.04370;1.44368;1.41421;,
 7.54370;1.87722;0.76537;,
 0.04370;1.87722;0.76537;,
 7.54370;2.02946;0.00000;,
 0.04370;2.02946;0.00000;,
 7.54370;1.87722;-0.76537;,
 0.04370;1.87722;-0.76537;,
 7.54370;1.44368;-1.41421;,
 0.04370;1.44368;-1.41421;,
 7.54370;0.79483;-1.84776;,
 0.04370;0.79483;-1.84776;,
 7.54370;0.02946;-2.00000;,
 0.04370;0.02946;-2.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 7.54370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;,
 0.04370;0.02946;0.00000;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 3;34,1,0;,
 3;35,4,1;,
 3;36,6,4;,
 3;37,8,6;,
 3;38,10,8;,
 3;39,12,10;,
 3;40,14,12;,
 3;41,16,14;,
 3;42,18,16;,
 3;43,20,18;,
 3;44,22,20;,
 3;45,24,22;,
 3;46,26,24;,
 3;47,28,26;,
 3;48,30,28;,
 3;49,32,30;,
 3;50,3,2;,
 3;51,2,5;,
 3;52,5,7;,
 3;53,7,9;,
 3;54,9,11;,
 3;55,11,13;,
 3;56,13,15;,
 3;57,15,17;,
 3;58,17,19;,
 3;59,19,21;,
 3;60,21,23;,
 3;61,23,25;,
 3;62,25,27;,
 3;63,27,29;,
 3;64,29,31;,
 3;65,31,33;;
 
 MeshMaterialList {
  5;
  48;
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
  Material {
   0.800000;0.608800;0.310400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.006400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.241600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.734400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  1.000000;0.000000;0.000000;,
  0.000000;-0.000001;-1.000000;,
  0.000000;-0.382685;-0.923879;,
  0.000000;-0.707108;-0.707106;,
  0.000000;-0.923878;-0.382688;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.923878;0.382688;,
  0.000000;-0.707108;0.707106;,
  0.000000;-0.382685;0.923879;,
  0.000000;-0.000001;1.000000;,
  0.000000;0.382684;0.923879;,
  0.000000;0.707108;0.707105;,
  0.000000;0.923880;0.382682;,
  0.000000;1.000000;0.000000;,
  0.000000;0.923880;-0.382682;,
  0.000000;0.707108;-0.707105;,
  0.000000;0.382684;-0.923879;,
  -1.000000;0.000000;0.000000;;
  48;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,1,1,16;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;;
 }
 MeshTextureCoords {
  66;
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.187500;0.000000;,
  0.187500;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.312500;0.000000;,
  0.312500;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.562500;0.000000;,
  0.562500;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.687500;0.000000;,
  0.687500;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.812500;0.000000;,
  0.812500;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.937500;0.000000;,
  0.937500;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}
