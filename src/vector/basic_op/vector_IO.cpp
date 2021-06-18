// #include<DD-AVX.hpp>
// #include<stdio.h>
// #include<string.h>
// #include<ctype.h>
// #define MM_BANNER		"%%MatrixMarket"
// #define MM_MTX			"matrix"
// #define MM_VEC			"vector"
// #define MM_FMT			"coordinate"
// #define MM_TYPE_REAL		"real"
// #define MM_TYPE_GENERAL		"general"
// #define MM_TYPE_SYMM		"symmetric"
//
// ///////////// dd_real_vector input ////////////////
// void dd_real_vector::input(const char* filename){
// #ifdef ddavx_debug
// 	 printf("DD_vector::input()\n");
// #endif
//    char	buf[256],banner[128];
//    FILE*	file;
//
//    if( filename==NULL )
//    {
//       printf("filename is NULL\n");
//       abort();
//    }
//    file = fopen(filename, "r");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//
//    if( fgets(buf, 256, file) == NULL )
//    {
//       printf("blank file %s\n",filename);
//       abort();
//    }
//
//    sscanf(buf, "%s", banner);
//    rewind(file);
//    if( strncmp(banner, "%%MatrixMarket", strlen("%%MatixMarket")) == 0)
//    {
//       input_mm(file);
//    }
//    else
//    {
//       input_plane(file);
//    }
//    rewind(file);
//    fclose(file);
// }
//
// void dd_real_vector::input_mm(FILE *file){
// #ifdef ddavx_debug
// 	 printf("    DD_vector::input_mm()\n");
// #endif
//    char	buf[1024];
//    char	banner[64], mtx[64], fmt[64], dtype[64], dstruct[64];
//    char	*p;
//    int	i;
//    int	err;
//    int	n;
//    int	idx;
//    double val;
//    rewind(file);
//
//    fgets(buf, 1024, file);
//    sscanf(buf, "%s %s %s %s %s", banner, mtx, fmt, dtype, dstruct);
//
//    for(p=mtx;*p!='\0';p++)     *p = (char)tolower(*p);
//    for(p=fmt;*p!='\0';p++)     *p = (char)tolower(*p);
//    for(p=dtype;*p!='\0';p++)   *p = (char)tolower(*p);
//    for(p=dstruct;*p!='\0';p++) *p = (char)tolower(*p);
//
//    if( strncmp(banner, MM_BANNER, strlen(MM_BANNER)) != 0)
//    {
//       printf("Not Matrix Market banner, banner is %s\n",banner);
//       abort();
//    }
//    if( strncmp(fmt, MM_FMT, strlen(MM_FMT))!=0 )
//    {
//       printf("Not Coodinate format\n");
//       abort();
//    }
//    if( strncmp(dtype, MM_TYPE_REAL, strlen(MM_TYPE_REAL))!=0 )
//    {
//       printf("Not real\n");
//       abort();
//    }
//    if( strncmp(dstruct, MM_TYPE_GENERAL, strlen(MM_TYPE_GENERAL))!=0 )
//    {
//       printf("Not general\n");
//       abort();
//    }
//
//    /* check size */
//    do
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("check size error\n");
// 	 abort();
//       }
//    }while( buf[0]=='%' );
//    if( sscanf(buf, "%d", &n) != 1 )
//    {
//       printf("file I/O error1\n");
//       abort();
//    }
//
//    /* read data */
//    N=n;
//    hi.resize(n*2);
//    lo = &hi[n];
//
//    for(i=0;i<n;i++)
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("cant read data, [row val]\n");
// 	 abort();
//       }
//       if( sscanf(buf,"%d %lf",&idx, &val) != 2 )
//       {
// 	 printf("not data, [row val]\n");
// 	 abort();
//       }
//       idx--;
//       hi[idx] = val;
//    }
// }
//
// void dd_real_vector::input_plane(FILE *file)
// {
// #ifdef ddavx_debug
// 	 printf("    DD_vector::input_plane()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    int	err;
//    int	n,is;
//    double	val;
//
//    /* check size */
//    n = 0;
//    do
//    {
//       err = fscanf(file, "%lf", &val);
//       if( err==1 ) n++;
//    }while( err==1 );
//    rewind(file);
//
//    /* read data */
//    N = n;
//    hi = new double[n*2];
//    lo = &hi[n];
//    is = 0;
//
//    for(i=0;i<n;i++)
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("cant read data, val\n");
// 	 abort();
//       }
//       if( sscanf(buf, "%lf", &val) != 1 )
//       {
// 	 printf("not data, val\n");
// 	 abort();
//       }
//       hi[i] = val;
//    }
// }
// ///////////// dd_real_vector output ////////////////
// void dd_real_vector::output_mm(const char *filename)
// {
// #ifdef ddavx_debug
//    printf("DD_vector::output_mm()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    FILE *file;
//
//    file = fopen(filename, "w");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//    if(N==0){
//       printf("vector size N is 0\n");
//       abort();
//    }
//
//    fprintf(file,"%s %s %s %s
//    %s\n",MM_BANNER,MM_VEC,MM_FMT,MM_TYPE_REAL,MM_TYPE_GENERAL);
//    for(i=0;i<N;i++)
//    {
//       fprintf(file,"%d %20.20e\n",i,hi[i]);
//    }
//
//    fclose(file);
// }
//
// void dd_real_vector::output_plane(const char *filename)
// {
// #ifdef ddavx_debug
// 	 printf("DD_vector::output_plane()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    FILE *file;
//
//    file = fopen(filename, "w");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//    if(N==0){
//       printf("vector size N is 0\n");
//       abort();
//    }
//    for(i=0;i<N;i++)
//    {
//       fprintf(file,"%20.20e\n",hi[i]);
//    }
//
//    fclose(file);
// }
// ///////////// d_real_vector input ////////////////
// void d_real_vector::input(const char* filename){
// #ifdef ddavx_debug
// 	 printf("D_vector::input()\n");
// #endif
//    char	buf[256],banner[128];
//    FILE*	file;
//
//    if( filename==NULL )
//    {
//       printf("filename is NULL\n");
//       abort();
//    }
//    file = fopen(filename, "r");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//
//    if( fgets(buf, 256, file) == NULL )
//    {
//       printf("blank file %s\n",filename);
//       abort();
//    }
//
//    sscanf(buf, "%s", banner);
//    rewind(file);
//    if( strncmp(banner, "%%MatrixMarket", strlen("%%MatixMarket")) == 0)
//    {
//       input_mm(file);
//    }
//    else
//    {
//       input_plane(file);
//    }
//    rewind(file);
//    fclose(file);
// }
// void d_real_vector::input_mm(FILE *file){
// #ifdef ddavx_debug
// 	 printf("    D_vector::input_mm()\n");
// #endif
//    char	buf[1024];
//    char	banner[64], mtx[64], fmt[64], dtype[64], dstruct[64];
//    char	*p;
//    int	i;
//    int	err;
//    int	n;
//    int	idx;
//    double val;
//    rewind(file);
//
//    fgets(buf, 1024, file);
//    sscanf(buf, "%s %s %s %s %s", banner, mtx, fmt, dtype, dstruct);
//
//    for(p=mtx;*p!='\0';p++)     *p = (char)tolower(*p);
//    for(p=fmt;*p!='\0';p++)     *p = (char)tolower(*p);
//    for(p=dtype;*p!='\0';p++)   *p = (char)tolower(*p);
//    for(p=dstruct;*p!='\0';p++) *p = (char)tolower(*p);
//
//    if( strncmp(banner, MM_BANNER, strlen(MM_BANNER)) != 0)
//    {
//       printf("Not Matrix Market banner, banner is %s\n",banner);
//       abort();
//    }
//    if( strncmp(fmt, MM_FMT, strlen(MM_FMT))!=0 )
//    {
//       printf("Not Coodinate format\n");
//       abort();
//    }
//    if( strncmp(dtype, MM_TYPE_REAL, strlen(MM_TYPE_REAL))!=0 )
//    {
//       printf("Not real\n");
//       abort();
//    }
//    if( strncmp(dstruct, MM_TYPE_GENERAL, strlen(MM_TYPE_GENERAL))!=0 )
//    {
//       printf("Not general\n");
//       abort();
//    }
//
//    /* check size */
//    do
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("check size error\n");
// 	 abort();
//       }
//    }while( buf[0]=='%' );
//    if( sscanf(buf, "%d", &n) != 1 )
//    {
//       printf("file I/O error1\n");
//       abort();
//    }
//
//    /* read data */
//    N=n;
//    hi.resize(n);
//
//    for(i=0;i<n;i++)
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("cant read data, row val\n");
// 	 abort();
//       }
//       printf("buf%s",buf);
//       if( sscanf(buf,"%d %lf",&idx, &val) != 2 )
//       {
// 	 printf("not data, row val\n");
// 	 abort();
//       }
//       printf("data%d %f\n",idx,val);
//       idx--;
//       hi[idx] = val;
//    }
// }
//
// void d_real_vector::input_plane(FILE *file)
// {
// #ifdef ddavx_debug
// 	 printf("    D_vector::input_plane()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    int	err;
//    int	n,is;
//    double	val;
//
//    /* check size */
//    n = 0;
//    do
//    {
//       err = fscanf(file, "%lf", &val);
//       if( err==1 ) n++;
//    }while( err==1 );
//    rewind(file);
//
//    /* read data */
//    N = n;
//    hi.resize(n, 0.0);
//    is = 0;
//
//    for(i=0;i<n;i++)
//    {
//       if( fgets(buf, 1024, file) == NULL )
//       {
// 	 printf("cant read data, val\n");
// 	 abort();
//       }
//       if( sscanf(buf, "%lf", &val) != 1 )
//       {
// 	 printf("not data, val\n");
// 	 abort();
//       }
//       hi[i] = val;
//    }
// }
// ///////////// d_real_vector output ////////////////
// void d_real_vector::output_mm(const char *filename)
// {
// #ifdef ddavx_debug
//    printf("D_vector::output_mm()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    FILE *file;
//
//    file = fopen(filename, "w");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//    if(N==0){
//       printf("vector size N is 0\n");
//       abort();
//    }
//
//    fprintf(file,"%s %s %s %s
//    %s\n",MM_BANNER,MM_VEC,MM_FMT,MM_TYPE_REAL,MM_TYPE_GENERAL);
//    for(i=0;i<N;i++)
//    {
//       fprintf(file,"%d %20.20e\n",i,hi[i]);
//    }
//
//    fclose(file);
// }
//
// void d_real_vector::output_plane(const char *filename)
// {
// #ifdef ddavx_debug
// 	 printf("D_vector::output_plane()\n");
// #endif
//    char	buf[1024];
//    int	i;
//    FILE *file;
//
//    file = fopen(filename, "w");
//    if( file==NULL )
//    {
//       printf("can not open file %s",filename);
//       abort();
//    }
//    if(N==0){
//       printf("vector size N is 0\n");
//       abort();
//    }
//    for(i=0;i<N;i++)
//    {
//       fprintf(file,"%20.20e\n",hi[i]);
//    }
//
//    fclose(file);
// }
