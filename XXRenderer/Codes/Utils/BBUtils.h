#ifndef BBUTILS_H
#define BBUTILS_H


#define BB_SAFE_DELETE(p) do{ delete p; p = NULL; } while(0)
#define BB_SAFE_DELETE_ARRAY(p) do{ delete []p; p = NULL; } while(0)
#define BB_PROCESS_ERROR(p) if(!p) break
#define BB_PROCESS_ERROR_RETURN(p) if(!p) return
#define BB_PROCESS_ERROR_RETURN_FALSE(p) if(!p) return false
#define BB_END(p) if(p) break
#define BB_SUCCEEDED(hr) (hr>=0)

#define BB_PATH_RESOURCE_SHADER(x) "../XXRenderer/resources/shaders/"#x
#define BB_PATH_RESOURCE_MESH(x) "../XXRenderer/resources/meshes/"#x

#define BB_CONSTANT_UPDATE_RATE 16
#define BB_CONSTANT_UPDATE_RATE_MS 0.016667

class BBUtils
{
public:
    static char *loadFileContent(const char *filePath, int &nFileSize);
};

#endif // BBUTILS_H
