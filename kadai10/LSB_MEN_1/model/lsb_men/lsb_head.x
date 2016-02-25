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
 169;
 0.49674;0.61666;0.00000;,
 0.50521;0.61473;0.03156;,
 0.43752;0.86686;0.04699;,
 0.43019;0.86456;0.01516;,
 0.52836;0.61331;0.05467;,
 0.45757;0.87700;0.07080;,
 0.55998;0.61279;0.06313;,
 0.48496;0.89226;0.08022;,
 0.59160;0.61331;0.05467;,
 0.51234;0.90856;0.07273;,
 0.61475;0.61473;0.03156;,
 0.53239;0.92153;0.05033;,
 0.62323;0.61666;0.00000;,
 0.53973;0.92769;0.01902;,
 0.61475;0.61859;-0.03156;,
 0.53239;0.92539;-0.01280;,
 0.59160;0.62000;-0.05467;,
 0.51234;0.91525;-0.03661;,
 0.55998;0.62052;-0.06313;,
 0.48496;0.89999;-0.04603;,
 0.52836;0.62000;-0.05467;,
 0.45757;0.88369;-0.03854;,
 0.50521;0.61859;-0.03156;,
 0.43752;0.87072;-0.01614;,
 0.49674;0.61666;0.00000;,
 0.43019;0.86456;0.01516;,
 0.25260;1.05143;0.05827;,
 0.24837;1.04604;0.02626;,
 0.26418;1.07003;0.08260;,
 0.27999;1.09685;0.09273;,
 0.29580;1.12470;0.08595;,
 0.30738;1.14613;0.06407;,
 0.31161;1.15538;0.03295;,
 0.30738;1.14999;0.00094;,
 0.29580;1.13139;-0.02339;,
 0.27999;1.10457;-0.03352;,
 0.26418;1.07672;-0.02674;,
 0.25260;1.05529;-0.00485;,
 0.24837;1.04604;0.02626;,
 0.00000;1.11899;0.06241;,
 0.00000;1.11247;0.03032;,
 0.00000;1.14068;0.08693;,
 0.00000;1.17173;0.09731;,
 0.00000;1.20381;0.09079;,
 0.00000;1.22833;0.06909;,
 0.00000;1.23872;0.03805;,
 0.00000;1.23219;0.00597;,
 0.00000;1.21050;-0.01855;,
 0.00000;1.17945;-0.02894;,
 0.00000;1.14737;-0.02241;,
 0.00000;1.12285;-0.00072;,
 0.00000;1.11247;0.03032;,
 -0.25260;1.05143;0.05827;,
 -0.24837;1.04604;0.02626;,
 -0.26418;1.07003;0.08260;,
 -0.27999;1.09685;0.09273;,
 -0.29580;1.12470;0.08595;,
 -0.30738;1.14613;0.06407;,
 -0.31161;1.15538;0.03295;,
 -0.30738;1.14999;0.00094;,
 -0.29580;1.13139;-0.02339;,
 -0.27999;1.10457;-0.03352;,
 -0.26418;1.07672;-0.02674;,
 -0.25260;1.05529;-0.00485;,
 -0.24837;1.04604;0.02626;,
 -0.43752;0.86686;0.04699;,
 -0.43019;0.86456;0.01516;,
 -0.45757;0.87700;0.07080;,
 -0.48496;0.89226;0.08022;,
 -0.51234;0.90856;0.07273;,
 -0.53239;0.92153;0.05033;,
 -0.53973;0.92769;0.01902;,
 -0.53239;0.92539;-0.01280;,
 -0.51234;0.91525;-0.03661;,
 -0.48496;0.89999;-0.04603;,
 -0.45757;0.88369;-0.03854;,
 -0.43752;0.87072;-0.01614;,
 -0.43019;0.86456;0.01516;,
 -0.50521;0.61473;0.03156;,
 -0.49674;0.61666;0.00000;,
 -0.52836;0.61331;0.05467;,
 -0.55998;0.61279;0.06313;,
 -0.59160;0.61331;0.05467;,
 -0.61475;0.61473;0.03156;,
 -0.62323;0.61666;0.00000;,
 -0.61475;0.61859;-0.03156;,
 -0.59160;0.62000;-0.05467;,
 -0.55998;0.62052;-0.06313;,
 -0.52836;0.62000;-0.05467;,
 -0.50521;0.61859;-0.03156;,
 -0.49674;0.61666;0.00000;,
 -0.43752;0.36259;0.01614;,
 -0.43019;0.36875;-0.01516;,
 -0.45757;0.34963;0.03854;,
 -0.48496;0.33333;0.04603;,
 -0.51234;0.31806;0.03661;,
 -0.53239;0.30792;0.01280;,
 -0.53973;0.30562;-0.01902;,
 -0.53239;0.31178;-0.05033;,
 -0.51234;0.32475;-0.07273;,
 -0.48496;0.34105;-0.08022;,
 -0.45757;0.35631;-0.07080;,
 -0.43752;0.36645;-0.04699;,
 -0.43019;0.36875;-0.01516;,
 -0.25260;0.17802;0.00485;,
 -0.24837;0.18727;-0.02626;,
 -0.26418;0.15659;0.02674;,
 -0.27999;0.12874;0.03352;,
 -0.29580;0.10192;0.02339;,
 -0.30738;0.08333;-0.00094;,
 -0.31161;0.07793;-0.03295;,
 -0.30738;0.08719;-0.06407;,
 -0.29580;0.10861;-0.08595;,
 -0.27999;0.13646;-0.09273;,
 -0.26418;0.16328;-0.08260;,
 -0.25260;0.18188;-0.05827;,
 -0.24837;0.18727;-0.02626;,
 0.00000;0.11046;0.00072;,
 0.00000;0.12085;-0.03032;,
 0.00000;0.08594;0.02241;,
 0.00000;0.05386;0.02894;,
 0.00000;0.02281;0.01855;,
 0.00000;0.00112;-0.00597;,
 0.00000;-0.00541;-0.03805;,
 0.00000;0.00498;-0.06909;,
 0.00000;0.02950;-0.09079;,
 0.00000;0.06158;-0.09731;,
 0.00000;0.09263;-0.08693;,
 0.00000;0.11432;-0.06241;,
 0.00000;0.12085;-0.03032;,
 0.25260;0.17802;0.00485;,
 0.24837;0.18727;-0.02626;,
 0.26418;0.15659;0.02674;,
 0.27999;0.12874;0.03352;,
 0.29580;0.10192;0.02339;,
 0.30738;0.08333;-0.00094;,
 0.31161;0.07793;-0.03295;,
 0.30738;0.08719;-0.06407;,
 0.29580;0.10861;-0.08595;,
 0.27999;0.13646;-0.09273;,
 0.26418;0.16328;-0.08260;,
 0.25260;0.18188;-0.05827;,
 0.24837;0.18727;-0.02626;,
 0.43752;0.36259;0.01614;,
 0.43019;0.36875;-0.01516;,
 0.45757;0.34963;0.03854;,
 0.48496;0.33333;0.04603;,
 0.51234;0.31806;0.03661;,
 0.53239;0.30792;0.01280;,
 0.53973;0.30562;-0.01902;,
 0.53239;0.31178;-0.05033;,
 0.51234;0.32475;-0.07273;,
 0.48496;0.34105;-0.08022;,
 0.45757;0.35631;-0.07080;,
 0.43752;0.36645;-0.04699;,
 0.43019;0.36875;-0.01516;,
 0.50521;0.61473;0.03156;,
 0.49674;0.61666;0.00000;,
 0.52836;0.61331;0.05467;,
 0.55998;0.61279;0.06313;,
 0.59160;0.61331;0.05467;,
 0.61475;0.61473;0.03156;,
 0.62323;0.61666;0.00000;,
 0.61475;0.61859;-0.03156;,
 0.59160;0.62000;-0.05467;,
 0.55998;0.62052;-0.06313;,
 0.52836;0.62000;-0.05467;,
 0.50521;0.61859;-0.03156;,
 0.49674;0.61666;0.00000;;
 
 144;
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
 4;3,2,26,27;,
 4;2,5,28,26;,
 4;5,7,29,28;,
 4;7,9,30,29;,
 4;9,11,31,30;,
 4;11,13,32,31;,
 4;13,15,33,32;,
 4;15,17,34,33;,
 4;17,19,35,34;,
 4;19,21,36,35;,
 4;21,23,37,36;,
 4;23,25,38,37;,
 4;27,26,39,40;,
 4;26,28,41,39;,
 4;28,29,42,41;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;37,38,51,50;,
 4;40,39,52,53;,
 4;39,41,54,52;,
 4;41,42,55,54;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;50,51,64,63;,
 4;53,52,65,66;,
 4;52,54,67,65;,
 4;54,55,68,67;,
 4;55,56,69,68;,
 4;56,57,70,69;,
 4;57,58,71,70;,
 4;58,59,72,71;,
 4;59,60,73,72;,
 4;60,61,74,73;,
 4;61,62,75,74;,
 4;62,63,76,75;,
 4;63,64,77,76;,
 4;66,65,78,79;,
 4;65,67,80,78;,
 4;67,68,81,80;,
 4;68,69,82,81;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;76,77,90,89;,
 4;79,78,91,92;,
 4;78,80,93,91;,
 4;80,81,94,93;,
 4;81,82,95,94;,
 4;82,83,96,95;,
 4;83,84,97,96;,
 4;84,85,98,97;,
 4;85,86,99,98;,
 4;86,87,100,99;,
 4;87,88,101,100;,
 4;88,89,102,101;,
 4;89,90,103,102;,
 4;92,91,104,105;,
 4;91,93,106,104;,
 4;93,94,107,106;,
 4;94,95,108,107;,
 4;95,96,109,108;,
 4;96,97,110,109;,
 4;97,98,111,110;,
 4;98,99,112,111;,
 4;99,100,113,112;,
 4;100,101,114,113;,
 4;101,102,115,114;,
 4;102,103,116,115;,
 4;105,104,117,118;,
 4;104,106,119,117;,
 4;106,107,120,119;,
 4;107,108,121,120;,
 4;108,109,122,121;,
 4;109,110,123,122;,
 4;110,111,124,123;,
 4;111,112,125,124;,
 4;112,113,126,125;,
 4;113,114,127,126;,
 4;114,115,128,127;,
 4;115,116,129,128;,
 4;118,117,130,131;,
 4;117,119,132,130;,
 4;119,120,133,132;,
 4;120,121,134,133;,
 4;121,122,135,134;,
 4;122,123,136,135;,
 4;123,124,137,136;,
 4;124,125,138,137;,
 4;125,126,139,138;,
 4;126,127,140,139;,
 4;127,128,141,140;,
 4;128,129,142,141;,
 4;131,130,143,144;,
 4;130,132,145,143;,
 4;132,133,146,145;,
 4;133,134,147,146;,
 4;134,135,148,147;,
 4;135,136,149,148;,
 4;136,137,150,149;,
 4;137,138,151,150;,
 4;138,139,152,151;,
 4;139,140,153,152;,
 4;140,141,154,153;,
 4;141,142,155,154;,
 4;144,143,156,157;,
 4;143,145,158,156;,
 4;145,146,159,158;,
 4;146,147,160,159;,
 4;147,148,161,160;,
 4;148,149,162,161;,
 4;149,150,163,162;,
 4;150,151,164,163;,
 4;151,152,165,164;,
 4;152,153,166,165;,
 4;153,154,167,166;,
 4;154,155,168,167;;
 
 MeshMaterialList {
  1;
  144;
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
  144;
  -1.000000;0.000000;-0.000002;,
  -0.865035;-0.030628;0.500776;,
  -0.498230;-0.052932;0.865428;,
  -0.000001;-0.061050;0.998135;,
  0.498231;-0.052932;0.865427;,
  0.865033;-0.030628;0.500779;,
  1.000000;0.000000;0.000001;,
  0.865033;0.030629;-0.500778;,
  0.498231;0.052932;-0.865427;,
  -0.000001;0.061049;-0.998135;,
  -0.498230;0.052931;-0.865428;,
  -0.865033;0.030628;-0.500779;,
  -0.866025;-0.499068;-0.030533;,
  -0.749143;-0.462341;0.474369;,
  -0.431478;-0.301581;0.850221;,
  -0.000002;-0.061049;0.998135;,
  0.431482;0.195719;0.880635;,
  0.749143;0.401082;0.527180;,
  0.866025;0.499068;0.030528;,
  0.749141;0.462338;-0.474375;,
  0.431482;0.301584;-0.850218;,
  0.000004;0.061052;-0.998135;,
  -0.431482;-0.195720;-0.880634;,
  -0.749142;-0.401082;-0.527181;,
  -0.500000;-0.864409;-0.052880;,
  -0.432518;-0.778375;0.455039;,
  -0.249112;-0.483603;0.839090;,
  0.000002;-0.061043;0.998135;,
  0.249115;0.377744;0.891769;,
  0.432518;0.717116;0.546509;,
  0.500001;0.864410;0.052870;,
  0.432516;0.778373;-0.455045;,
  0.249117;0.483609;-0.839085;,
  0.000002;0.061050;-0.998135;,
  -0.249117;-0.377747;-0.891767;,
  -0.432516;-0.717112;-0.546516;,
  0.000000;-0.998134;-0.061056;,
  0.000000;-0.894051;0.447965;,
  0.000000;-0.550226;0.835016;,
  0.000000;-0.061037;0.998136;,
  -0.000000;0.444370;0.895843;,
  0.000000;0.832793;0.553584;,
  0.000000;0.998135;0.061046;,
  0.000000;0.894050;-0.447966;,
  0.000000;0.550237;-0.835009;,
  0.000000;0.061046;-0.998135;,
  0.000000;-0.444373;-0.895842;,
  0.000000;-0.832787;-0.553594;,
  0.500000;-0.864409;-0.052880;,
  0.432518;-0.778375;0.455039;,
  0.249112;-0.483602;0.839090;,
  -0.000002;-0.061043;0.998135;,
  -0.249114;0.377743;0.891769;,
  -0.432518;0.717117;0.546508;,
  -0.500000;0.864410;0.052868;,
  -0.432516;0.778373;-0.455045;,
  -0.249117;0.483609;-0.839085;,
  -0.000002;0.061050;-0.998135;,
  0.249117;-0.377747;-0.891767;,
  0.432516;-0.717112;-0.546516;,
  0.866025;-0.499068;-0.030534;,
  0.749143;-0.462341;0.474369;,
  0.431478;-0.301581;0.850221;,
  0.000002;-0.061049;0.998135;,
  -0.431480;0.195718;0.880636;,
  -0.749143;0.401082;0.527179;,
  -0.866025;0.499068;0.030525;,
  -0.749140;0.462339;-0.474375;,
  -0.431481;0.301584;-0.850218;,
  -0.000004;0.061052;-0.998135;,
  0.431482;-0.195720;-0.880634;,
  0.749142;-0.401082;-0.527181;,
  1.000000;-0.000000;-0.000001;,
  0.865037;-0.030628;0.500772;,
  0.498231;-0.052932;0.865427;,
  0.000002;-0.061050;0.998135;,
  -0.498232;-0.052932;0.865426;,
  -0.865035;-0.030629;0.500775;,
  -1.000000;0.000000;-0.000001;,
  -0.865035;0.030629;-0.500776;,
  -0.498232;0.052932;-0.865426;,
  0.000002;0.061050;-0.998135;,
  0.498227;0.052931;-0.865429;,
  0.865034;0.030628;-0.500777;,
  0.866026;0.499067;0.030530;,
  0.749144;0.401082;0.527178;,
  0.431483;0.195721;0.880634;,
  -0.000002;-0.061051;0.998135;,
  -0.431481;-0.301584;0.850218;,
  -0.749141;-0.462339;0.474374;,
  -0.866025;-0.499068;-0.030526;,
  -0.749141;-0.401080;-0.527183;,
  -0.431480;-0.195719;-0.880635;,
  0.000003;0.061048;-0.998135;,
  0.431475;0.301580;-0.850223;,
  0.749141;0.462339;-0.474374;,
  0.500000;0.864410;0.052873;,
  0.432517;0.717115;0.546512;,
  0.249117;0.377743;0.891768;,
  -0.000002;-0.061050;0.998135;,
  -0.249116;-0.483609;0.839085;,
  -0.432516;-0.778371;0.455047;,
  -0.500001;-0.864410;-0.052869;,
  -0.432516;-0.717112;-0.546516;,
  -0.249116;-0.377746;-0.891767;,
  -0.000003;0.061043;-0.998135;,
  0.249114;0.483607;-0.839087;,
  0.432518;0.778374;-0.455041;,
  0.000000;0.998135;0.061043;,
  -0.000001;0.832792;0.553586;,
  -0.000000;0.444363;0.895847;,
  -0.000001;-0.061048;0.998135;,
  -0.000001;-0.550234;0.835011;,
  0.000000;-0.894050;0.447968;,
  0.000000;-0.998135;-0.061050;,
  0.000000;-0.832789;-0.553591;,
  -0.000000;-0.444377;-0.895840;,
  -0.000000;0.061041;-0.998135;,
  -0.000000;0.550237;-0.835008;,
  0.000000;0.894051;-0.447964;,
  -0.500000;0.864411;0.052866;,
  -0.432517;0.717116;0.546510;,
  -0.249114;0.377741;0.891770;,
  0.000001;-0.061049;0.998135;,
  0.249114;-0.483605;0.839088;,
  0.432517;-0.778374;0.455042;,
  0.500000;-0.864410;-0.052870;,
  0.432516;-0.717115;-0.546513;,
  0.249116;-0.377748;-0.891766;,
  0.000003;0.061043;-0.998135;,
  -0.249115;0.483611;-0.839084;,
  -0.432517;0.778374;-0.455042;,
  -0.866025;0.499068;0.030525;,
  -0.749141;0.401082;0.527182;,
  -0.431480;0.195719;0.880636;,
  0.000003;-0.061050;0.998135;,
  0.431478;-0.301581;0.850221;,
  0.749139;-0.462339;0.474376;,
  0.866024;-0.499069;-0.030523;,
  0.749141;-0.401081;-0.527183;,
  0.431479;-0.195719;-0.880636;,
  -0.000000;0.061047;-0.998135;,
  -0.431479;0.301582;-0.850220;,
  -0.749139;0.462339;-0.474377;;
  144;
  4;0,1,13,12;,
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;7,8,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,0,12,23;,
  4;12,13,25,24;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;23,12,24,35;,
  4;24,25,37,36;,
  4;25,26,38,37;,
  4;26,27,39,38;,
  4;27,28,40,39;,
  4;28,29,41,40;,
  4;29,30,42,41;,
  4;30,31,43,42;,
  4;31,32,44,43;,
  4;32,33,45,44;,
  4;33,34,46,45;,
  4;34,35,47,46;,
  4;35,24,36,47;,
  4;36,37,49,48;,
  4;37,38,50,49;,
  4;38,39,51,50;,
  4;39,40,52,51;,
  4;40,41,53,52;,
  4;41,42,54,53;,
  4;42,43,55,54;,
  4;43,44,56,55;,
  4;44,45,57,56;,
  4;45,46,58,57;,
  4;46,47,59,58;,
  4;47,36,48,59;,
  4;48,49,61,60;,
  4;49,50,62,61;,
  4;50,51,63,62;,
  4;51,52,64,63;,
  4;52,53,65,64;,
  4;53,54,66,65;,
  4;54,55,67,66;,
  4;55,56,68,67;,
  4;56,57,69,68;,
  4;57,58,70,69;,
  4;58,59,71,70;,
  4;59,48,60,71;,
  4;60,61,73,72;,
  4;61,62,74,73;,
  4;62,63,75,74;,
  4;63,64,76,75;,
  4;64,65,77,76;,
  4;65,66,78,77;,
  4;66,67,79,78;,
  4;67,68,80,79;,
  4;68,69,81,80;,
  4;69,70,82,81;,
  4;70,71,83,82;,
  4;71,60,72,83;,
  4;72,73,85,84;,
  4;73,74,86,85;,
  4;74,75,87,86;,
  4;75,76,88,87;,
  4;76,77,89,88;,
  4;77,78,90,89;,
  4;78,79,91,90;,
  4;79,80,92,91;,
  4;80,81,93,92;,
  4;81,82,94,93;,
  4;82,83,95,94;,
  4;83,72,84,95;,
  4;84,85,97,96;,
  4;85,86,98,97;,
  4;86,87,99,98;,
  4;87,88,100,99;,
  4;88,89,101,100;,
  4;89,90,102,101;,
  4;90,91,103,102;,
  4;91,92,104,103;,
  4;92,93,105,104;,
  4;93,94,106,105;,
  4;94,95,107,106;,
  4;95,84,96,107;,
  4;96,97,109,108;,
  4;97,98,110,109;,
  4;98,99,111,110;,
  4;99,100,112,111;,
  4;100,101,113,112;,
  4;101,102,114,113;,
  4;102,103,115,114;,
  4;103,104,116,115;,
  4;104,105,117,116;,
  4;105,106,118,117;,
  4;106,107,119,118;,
  4;107,96,108,119;,
  4;108,109,121,120;,
  4;109,110,122,121;,
  4;110,111,123,122;,
  4;111,112,124,123;,
  4;112,113,125,124;,
  4;113,114,126,125;,
  4;114,115,127,126;,
  4;115,116,128,127;,
  4;116,117,129,128;,
  4;117,118,130,129;,
  4;118,119,131,130;,
  4;119,108,120,131;,
  4;120,121,133,132;,
  4;121,122,134,133;,
  4;122,123,135,134;,
  4;123,124,136,135;,
  4;124,125,137,136;,
  4;125,126,138,137;,
  4;126,127,139,138;,
  4;127,128,140,139;,
  4;128,129,141,140;,
  4;129,130,142,141;,
  4;130,131,143,142;,
  4;131,120,132,143;,
  4;132,133,1,0;,
  4;133,134,2,1;,
  4;134,135,3,2;,
  4;135,136,4,3;,
  4;136,137,5,4;,
  4;137,138,6,5;,
  4;138,139,7,6;,
  4;139,140,8,7;,
  4;140,141,9,8;,
  4;141,142,10,9;,
  4;142,143,11,10;,
  4;143,132,0,11;;
 }
 MeshTextureCoords {
  169;
  0.000000;0.000000;,
  0.000000;0.083330;,
  0.083330;0.083330;,
  0.083330;0.000000;,
  0.000000;0.166670;,
  0.083330;0.166670;,
  0.000000;0.250000;,
  0.083330;0.250000;,
  0.000000;0.333330;,
  0.083330;0.333330;,
  0.000000;0.416670;,
  0.083330;0.416670;,
  0.000000;0.500000;,
  0.083330;0.500000;,
  0.000000;0.583330;,
  0.083330;0.583330;,
  0.000000;0.666670;,
  0.083330;0.666670;,
  0.000000;0.750000;,
  0.083330;0.750000;,
  0.000000;0.833330;,
  0.083330;0.833330;,
  0.000000;0.916670;,
  0.083330;0.916670;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.166670;0.083330;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.166670;0.250000;,
  0.166670;0.333330;,
  0.166670;0.416670;,
  0.166670;0.500000;,
  0.166670;0.583330;,
  0.166670;0.666670;,
  0.166670;0.750000;,
  0.166670;0.833330;,
  0.166670;0.916670;,
  0.166670;1.000000;,
  0.250000;0.083330;,
  0.250000;0.000000;,
  0.250000;0.166670;,
  0.250000;0.250000;,
  0.250000;0.333330;,
  0.250000;0.416670;,
  0.250000;0.500000;,
  0.250000;0.583330;,
  0.250000;0.666670;,
  0.250000;0.750000;,
  0.250000;0.833330;,
  0.250000;0.916670;,
  0.250000;1.000000;,
  0.333330;0.083330;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.333330;0.250000;,
  0.333330;0.333330;,
  0.333330;0.416670;,
  0.333330;0.500000;,
  0.333330;0.583330;,
  0.333330;0.666670;,
  0.333330;0.750000;,
  0.333330;0.833330;,
  0.333330;0.916670;,
  0.333330;1.000000;,
  0.416670;0.083330;,
  0.416670;0.000000;,
  0.416670;0.166670;,
  0.416670;0.250000;,
  0.416670;0.333330;,
  0.416670;0.416670;,
  0.416670;0.500000;,
  0.416670;0.583330;,
  0.416670;0.666670;,
  0.416670;0.750000;,
  0.416670;0.833330;,
  0.416670;0.916670;,
  0.416670;1.000000;,
  0.500000;0.083330;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.500000;0.250000;,
  0.500000;0.333330;,
  0.500000;0.416670;,
  0.500000;0.500000;,
  0.500000;0.583330;,
  0.500000;0.666670;,
  0.500000;0.750000;,
  0.500000;0.833330;,
  0.500000;0.916670;,
  0.500000;1.000000;,
  0.583330;0.083330;,
  0.583330;0.000000;,
  0.583330;0.166670;,
  0.583330;0.250000;,
  0.583330;0.333330;,
  0.583330;0.416670;,
  0.583330;0.500000;,
  0.583330;0.583330;,
  0.583330;0.666670;,
  0.583330;0.750000;,
  0.583330;0.833330;,
  0.583330;0.916670;,
  0.583330;1.000000;,
  0.666670;0.083330;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.666670;0.250000;,
  0.666670;0.333330;,
  0.666670;0.416670;,
  0.666670;0.500000;,
  0.666670;0.583330;,
  0.666670;0.666670;,
  0.666670;0.750000;,
  0.666670;0.833330;,
  0.666670;0.916670;,
  0.666670;1.000000;,
  0.750000;0.083330;,
  0.750000;0.000000;,
  0.750000;0.166670;,
  0.750000;0.250000;,
  0.750000;0.333330;,
  0.750000;0.416670;,
  0.750000;0.500000;,
  0.750000;0.583330;,
  0.750000;0.666670;,
  0.750000;0.750000;,
  0.750000;0.833330;,
  0.750000;0.916670;,
  0.750000;1.000000;,
  0.833330;0.083330;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  0.833330;0.250000;,
  0.833330;0.333330;,
  0.833330;0.416670;,
  0.833330;0.500000;,
  0.833330;0.583330;,
  0.833330;0.666670;,
  0.833330;0.750000;,
  0.833330;0.833330;,
  0.833330;0.916670;,
  0.833330;1.000000;,
  0.916670;0.083330;,
  0.916670;0.000000;,
  0.916670;0.166670;,
  0.916670;0.250000;,
  0.916670;0.333330;,
  0.916670;0.416670;,
  0.916670;0.500000;,
  0.916670;0.583330;,
  0.916670;0.666670;,
  0.916670;0.750000;,
  0.916670;0.833330;,
  0.916670;0.916670;,
  0.916670;1.000000;,
  1.000000;0.083330;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  1.000000;0.250000;,
  1.000000;0.333330;,
  1.000000;0.416670;,
  1.000000;0.500000;,
  1.000000;0.583330;,
  1.000000;0.666670;,
  1.000000;0.750000;,
  1.000000;0.833330;,
  1.000000;0.916670;,
  1.000000;1.000000;;
 }
 MeshVertexColors {
  169;
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
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;,
  146;1.000000;1.000000;1.000000;1.000000;,
  147;1.000000;1.000000;1.000000;1.000000;,
  148;1.000000;1.000000;1.000000;1.000000;,
  149;1.000000;1.000000;1.000000;1.000000;,
  150;1.000000;1.000000;1.000000;1.000000;,
  151;1.000000;1.000000;1.000000;1.000000;,
  152;1.000000;1.000000;1.000000;1.000000;,
  153;1.000000;1.000000;1.000000;1.000000;,
  154;1.000000;1.000000;1.000000;1.000000;,
  155;1.000000;1.000000;1.000000;1.000000;,
  156;1.000000;1.000000;1.000000;1.000000;,
  157;1.000000;1.000000;1.000000;1.000000;,
  158;1.000000;1.000000;1.000000;1.000000;,
  159;1.000000;1.000000;1.000000;1.000000;,
  160;1.000000;1.000000;1.000000;1.000000;,
  161;1.000000;1.000000;1.000000;1.000000;,
  162;1.000000;1.000000;1.000000;1.000000;,
  163;1.000000;1.000000;1.000000;1.000000;,
  164;1.000000;1.000000;1.000000;1.000000;,
  165;1.000000;1.000000;1.000000;1.000000;,
  166;1.000000;1.000000;1.000000;1.000000;,
  167;1.000000;1.000000;1.000000;1.000000;,
  168;1.000000;1.000000;1.000000;1.000000;;
 }
}