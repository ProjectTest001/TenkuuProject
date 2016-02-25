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
 78;
 -0.81000;-0.04654;-0.05927;,
 -0.81025;-0.01677;-0.07145;,
 0.00512;-0.01231;-0.07723;,
 0.00537;-0.04207;-0.06505;,
 -0.81042;0.01537;-0.07046;,
 0.00496;0.01983;-0.07625;,
 -0.81048;0.04434;-0.05649;,
 0.00490;0.04880;-0.06228;,
 -0.81042;0.06512;-0.03195;,
 0.00496;0.06958;-0.03773;,
 -0.81025;0.07412;-0.00108;,
 0.00513;0.07858;-0.00686;,
 -0.81000;0.06979;0.03079;,
 0.00538;0.07425;0.02500;,
 -0.80971;0.05287;0.05813;,
 0.00566;0.05733;0.05235;,
 -0.80944;0.02629;0.07623;,
 0.00594;0.03075;0.07045;,
 -0.80922;-0.00536;0.08196;,
 0.00615;-0.00090;0.07618;,
 -0.80911;-0.03660;0.07432;,
 0.00627;-0.03213;0.06854;,
 -0.80911;-0.06203;0.05463;,
 0.00627;-0.05756;0.04885;,
 -0.80922;-0.07725;0.02631;,
 0.00615;-0.07279;0.02052;,
 -0.80944;-0.07964;-0.00576;,
 0.00594;-0.07518;-0.01155;,
 -0.80972;-0.06878;-0.03603;,
 0.00566;-0.06431;-0.04182;,
 -0.81000;-0.04654;-0.05927;,
 0.00537;-0.04207;-0.06505;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 -0.80979;-0.00301;0.00465;,
 0.00518;0.00066;0.00018;,
 0.00496;-0.04288;-0.06374;,
 0.00471;-0.01311;-0.07592;,
 0.00518;0.00066;0.00018;,
 0.00455;0.01903;-0.07494;,
 0.00518;0.00066;0.00018;,
 0.00448;0.04800;-0.06096;,
 0.00518;0.00066;0.00018;,
 0.00455;0.06879;-0.03643;,
 0.00518;0.00066;0.00018;,
 0.00471;0.07778;-0.00555;,
 0.00518;0.00066;0.00018;,
 0.00497;0.07345;0.02632;,
 0.00518;0.00066;0.00018;,
 0.00525;0.05653;0.05366;,
 0.00518;0.00066;0.00018;,
 0.00553;0.02995;0.07176;,
 0.00518;0.00066;0.00018;,
 0.00574;-0.00169;0.07749;,
 0.00518;0.00066;0.00018;,
 0.00586;-0.03294;0.06985;,
 0.00518;0.00066;0.00018;,
 0.00586;-0.05837;0.05016;,
 0.00518;0.00066;0.00018;,
 0.00574;-0.07358;0.02183;,
 0.00518;0.00066;0.00018;,
 0.00552;-0.07598;-0.01024;,
 0.00518;0.00066;0.00018;,
 0.00525;-0.06511;-0.04051;,
 0.00518;0.00066;0.00018;,
 0.00496;-0.04288;-0.06374;;
 
 45;
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
 3;32,1,0;,
 3;33,4,1;,
 3;34,6,4;,
 3;35,8,6;,
 3;36,10,8;,
 3;37,12,10;,
 3;38,14,12;,
 3;39,16,14;,
 3;40,18,16;,
 3;41,20,18;,
 3;42,22,20;,
 3;43,24,22;,
 3;44,26,24;,
 3;45,28,26;,
 3;46,30,28;,
 3;47,48,49;,
 3;50,49,51;,
 3;52,51,53;,
 3;54,53,55;,
 3;56,55,57;,
 3;58,57,59;,
 3;60,59,61;,
 3;62,61,63;,
 3;64,63,65;,
 3;66,65,67;,
 3;68,67,69;,
 3;70,69,71;,
 3;72,71,73;,
 3;74,73,75;,
 3;76,75,77;;
 
 MeshMaterialList {
  1;
  45;
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
  Material {
   0.029260;0.027500;0.220000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.126350;0.118750;0.950000;;
  }
 }
 MeshNormals {
  47;
  -0.999960;-0.005477;0.007093;,
  -0.002780;-0.562831;-0.826567;,
  -0.006005;-0.177980;-0.984016;,
  -0.008192;0.237582;-0.971333;,
  -0.008961;0.612122;-0.790713;,
  -0.008180;0.880827;-0.473368;,
  -0.005985;0.997224;-0.074215;,
  -0.002755;0.941189;0.337870;,
  0.000950;0.722415;0.691459;,
  0.004489;0.378746;0.925490;,
  0.007253;-0.030422;0.999511;,
  0.008765;-0.434306;0.900723;,
  0.008760;-0.763152;0.646160;,
  0.007238;-0.960009;0.279875;,
  0.004468;-0.990868;-0.134761;,
  0.000925;-0.850397;-0.526140;,
  0.999960;0.005499;-0.007102;,
  0.999959;0.005479;-0.007161;,
  0.999960;0.005450;-0.007105;,
  0.999959;0.005508;-0.007123;,
  0.999960;0.005478;-0.007113;,
  0.999959;0.005503;-0.007131;,
  0.999960;0.005452;-0.007079;,
  0.999960;0.005523;-0.007075;,
  0.999959;0.005492;-0.007136;,
  0.999960;0.005459;-0.007072;,
  0.999960;0.005516;-0.007096;,
  0.999960;0.005476;-0.007104;,
  0.999960;0.005475;-0.007141;,
  0.999959;0.005456;-0.007169;,
  0.999960;0.005413;-0.007079;,
  0.999960;0.005479;-0.007112;,
  -0.999959;-0.005534;0.007115;,
  -0.999960;-0.005528;0.007026;,
  -0.999960;-0.005457;0.007062;,
  -0.999960;-0.005485;0.007090;,
  -0.999960;-0.005434;0.007112;,
  -0.999960;-0.005448;0.007111;,
  -0.999960;-0.005420;0.007070;,
  -0.999960;-0.005463;0.007070;,
  -0.999959;-0.005512;0.007133;,
  -0.999960;-0.005478;0.007126;,
  -0.999960;-0.005463;0.007126;,
  -0.999960;-0.005498;0.007086;,
  -0.999960;-0.005515;0.007103;,
  -0.999959;-0.005497;0.007149;,
  -0.999961;-0.005424;0.007022;;
  45;
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
  4;15,1,1,15;,
  3;0,32,33;,
  3;0,34,32;,
  3;0,35,34;,
  3;0,36,35;,
  3;0,37,36;,
  3;0,38,37;,
  3;0,39,38;,
  3;0,40,39;,
  3;0,41,40;,
  3;0,42,41;,
  3;0,43,42;,
  3;0,44,43;,
  3;0,45,44;,
  3;0,46,45;,
  3;0,33,46;,
  3;31,16,17;,
  3;31,17,18;,
  3;31,18,19;,
  3;31,19,20;,
  3;31,20,21;,
  3;31,21,22;,
  3;31,22,23;,
  3;31,23,24;,
  3;31,24,25;,
  3;31,25,26;,
  3;31,26,27;,
  3;31,27,28;,
  3;31,28,29;,
  3;31,29,30;,
  3;31,30,16;;
 }
 MeshTextureCoords {
  78;
  0.000000;0.000000;,
  0.066670;0.000000;,
  0.066670;0.333330;,
  0.000000;0.333330;,
  0.133330;0.000000;,
  0.133330;0.333330;,
  0.200000;0.000000;,
  0.200000;0.333330;,
  0.266670;0.000000;,
  0.266670;0.333330;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.400000;0.000000;,
  0.400000;0.333330;,
  0.466670;0.000000;,
  0.466670;0.333330;,
  0.533330;0.000000;,
  0.533330;0.333330;,
  0.600000;0.000000;,
  0.600000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  0.733330;0.000000;,
  0.733330;0.333330;,
  0.800000;0.000000;,
  0.800000;0.333330;,
  0.866670;0.000000;,
  0.866670;0.333330;,
  0.933330;0.000000;,
  0.933330;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.033330;0.000000;,
  0.100000;0.000000;,
  0.166670;0.000000;,
  0.233330;0.000000;,
  0.300000;0.000000;,
  0.366670;0.000000;,
  0.433330;0.000000;,
  0.500000;0.000000;,
  0.566670;0.000000;,
  0.633330;0.000000;,
  0.700000;0.000000;,
  0.766670;0.000000;,
  0.833330;0.000000;,
  0.900000;0.000000;,
  0.966670;0.000000;,
  0.033330;1.000000;,
  0.000000;1.000000;,
  0.066670;1.000000;,
  0.100000;1.000000;,
  0.133330;1.000000;,
  0.166670;1.000000;,
  0.200000;1.000000;,
  0.233330;1.000000;,
  0.266670;1.000000;,
  0.300000;1.000000;,
  0.333330;1.000000;,
  0.366670;1.000000;,
  0.400000;1.000000;,
  0.433330;1.000000;,
  0.466670;1.000000;,
  0.500000;1.000000;,
  0.533330;1.000000;,
  0.566670;1.000000;,
  0.600000;1.000000;,
  0.633330;1.000000;,
  0.666670;1.000000;,
  0.700000;1.000000;,
  0.733330;1.000000;,
  0.766670;1.000000;,
  0.800000;1.000000;,
  0.833330;1.000000;,
  0.866670;1.000000;,
  0.900000;1.000000;,
  0.933330;1.000000;,
  0.966670;1.000000;,
  1.000000;1.000000;;
 }
 MeshVertexColors {
  78;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;;
 }
}