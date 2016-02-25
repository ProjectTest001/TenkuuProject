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
 -0.41199;0.04549;-0.06172;,
 -0.41160;0.06678;-0.03761;,
 -0.00155;0.06543;-0.03845;,
 -0.00194;0.04414;-0.06256;,
 -0.41171;0.07642;-0.00693;,
 -0.00166;0.07507;-0.00777;,
 -0.41231;0.07276;0.02501;,
 -0.00226;0.07141;0.02417;,
 -0.41329;0.05644;0.05270;,
 -0.00324;0.05509;0.05185;,
 -0.41448;0.03027;0.07134;,
 -0.00444;0.02892;0.07049;,
 -0.41568;-0.00122;0.07771;,
 -0.00564;-0.00258;0.07687;,
 -0.41668;-0.03259;0.07071;,
 -0.00664;-0.03395;0.06986;,
 -0.41731;-0.05841;0.05155;,
 -0.00726;-0.05976;0.05070;,
 -0.41745;-0.07422;0.02354;,
 -0.00741;-0.07557;0.02270;,
 -0.41709;-0.07728;-0.00846;,
 -0.00704;-0.07863;-0.00931;,
 -0.41628;-0.06707;-0.03894;,
 -0.00624;-0.06842;-0.03979;,
 -0.41517;-0.04535;-0.06262;,
 -0.00513;-0.04670;-0.06347;,
 -0.41395;-0.01587;-0.07541;,
 -0.00390;-0.01722;-0.07626;,
 -0.41282;0.01626;-0.07509;,
 -0.00278;0.01491;-0.07593;,
 -0.41199;0.04549;-0.06172;,
 -0.00194;0.04414;-0.06256;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.41452;-0.00050;0.00039;,
 -0.00474;-0.00335;-0.00079;,
 -0.00220;0.04265;-0.06289;,
 -0.00181;0.06393;-0.03878;,
 -0.00474;-0.00335;-0.00079;,
 -0.00192;0.07357;-0.00810;,
 -0.00474;-0.00335;-0.00079;,
 -0.00253;0.06992;0.02385;,
 -0.00474;-0.00335;-0.00079;,
 -0.00350;0.05360;0.05153;,
 -0.00474;-0.00335;-0.00079;,
 -0.00470;0.02742;0.07017;,
 -0.00474;-0.00335;-0.00079;,
 -0.00590;-0.00407;0.07654;,
 -0.00474;-0.00335;-0.00079;,
 -0.00690;-0.03544;0.06954;,
 -0.00474;-0.00335;-0.00079;,
 -0.00752;-0.06126;0.05038;,
 -0.00474;-0.00335;-0.00079;,
 -0.00767;-0.07707;0.02237;,
 -0.00474;-0.00335;-0.00079;,
 -0.00731;-0.08013;-0.00964;,
 -0.00474;-0.00335;-0.00079;,
 -0.00650;-0.06991;-0.04011;,
 -0.00474;-0.00335;-0.00079;,
 -0.00539;-0.04819;-0.06379;,
 -0.00474;-0.00335;-0.00079;,
 -0.00416;-0.01871;-0.07658;,
 -0.00474;-0.00335;-0.00079;,
 -0.00304;0.01341;-0.07626;,
 -0.00474;-0.00335;-0.00079;,
 -0.00220;0.04265;-0.06289;;
 
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
  -0.999274;0.035147;-0.014699;,
  0.000311;0.595794;-0.803137;,
  0.001862;0.870848;-0.491550;,
  0.003090;0.995465;-0.095081;,
  0.003784;0.948122;0.317883;,
  0.003826;0.736772;0.676130;,
  0.003201;0.397825;0.917456;,
  0.002021;-0.010028;0.999948;,
  0.000499;-0.415937;0.909394;,
  -0.001108;-0.749699;0.661778;,
  -0.002526;-0.953959;0.299926;,
  -0.003509;-0.993497;-0.113806;,
  -0.003887;-0.861324;-0.508041;,
  -0.003593;-0.580015;-0.814597;,
  -0.002677;-0.198204;-0.980157;,
  -0.001294;0.217774;-0.975998;,
  0.999274;-0.035168;0.014682;,
  0.999274;-0.035148;0.014681;,
  0.999273;-0.035154;0.014757;,
  0.999275;-0.035107;0.014750;,
  0.999277;-0.035089;0.014660;,
  0.999274;-0.035154;0.014701;,
  0.999273;-0.035172;0.014721;,
  0.999275;-0.035113;0.014736;,
  0.999275;-0.035121;0.014704;,
  0.999274;-0.035147;0.014705;,
  0.999275;-0.035125;0.014686;,
  0.999274;-0.035148;0.014671;,
  0.999273;-0.035166;0.014714;,
  0.999276;-0.035109;0.014696;,
  0.999275;-0.035133;0.014671;,
  0.999274;-0.035137;0.014702;,
  -0.999273;0.035172;-0.014715;,
  -0.999273;0.035178;-0.014726;,
  -0.999272;0.035183;-0.014724;,
  -0.999273;0.035163;-0.014710;,
  -0.999276;0.035131;-0.014642;,
  -0.999274;0.035166;-0.014647;,
  -0.999274;0.035174;-0.014670;,
  -0.999274;0.035163;-0.014656;,
  -0.999274;0.035139;-0.014705;,
  -0.999276;0.035097;-0.014724;,
  -0.999276;0.035112;-0.014687;,
  -0.999274;0.035136;-0.014735;,
  -0.999275;0.035097;-0.014730;,
  -0.999276;0.035106;-0.014700;,
  -0.999272;0.035189;-0.014712;;
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
