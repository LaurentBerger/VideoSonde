#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace std;
using namespace cv;

struct VideoUI {
    Mat x;
    vector<Point> v;
    String nomFenetre = "Video";
};

void GestionCrayon(int evt, int x, int y, int type, void *extra);


int main(int argc, char **argv)
{
    if (argc!=2)
    {
        cout << "Syntaxe :\n VideoSonde nomFichier.mp4";
        return 0;
    }
    VideoCapture fVideo(argv[1]);
    if (!fVideo.isOpened())
    {
        cout << argv[1] << "impossible d'utiliser ce fichier\n";
        return 0;
    }
    VideoUI v;
    
    fVideo>>v.x;
    if (v.x.rows == 0)
    {
        cout << argv[1] << "problème dans le décodage ou image vide\n";
        return 0;

    }
    double xEnd = fVideo.get(CAP_PROP_FRAME_COUNT);
    cout << "Nombre d'images dans la vidéo : " << xEnd << "\n";
    double fps = fVideo.get(CAP_PROP_FPS);
    cout << "Nombre d'images pas seconde dans la vidéo : " << fps << "\n";
    cout<<"taille image : "<<v.x.rows<< " lignes X "<<v.x.cols<<" colonnes\n";
    int code=0;
    namedWindow(v.nomFenetre);
    setMouseCallback(v.nomFenetre, GestionCrayon, &v);
    int indImage=0;
    Mat y;
    while (code != 27)
    {
        for (int i = 0; i < v.v.size(); i++)
        {
            circle(v.x, v.v[i], 5, Scalar(0,255,0), -1);
        }
        putText(v.x,format("%d",indImage),Point(50,50),FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255));
        resize(v.x,y,Size(),2,2);
        imshow(v.nomFenetre,y);

        code = waitKey(30);
        switch(code) {
        case 'n':
            indImage++;
            if (indImage < xEnd)
            {
                fVideo.set(CAP_PROP_POS_FRAMES, indImage);
                fVideo >> v.x;
            }
            break;
        case 'p':
            indImage--;
            if (indImage >= 0)
            {
                fVideo.set(CAP_PROP_POS_FRAMES, indImage);
                fVideo >> v.x;
            }
            break;
        case 'N':
            indImage+=10;
            if (indImage < xEnd)
            {
                fVideo.set(CAP_PROP_POS_FRAMES, indImage);
                fVideo >> v.x;
            }
            break;
        case 'P':
            indImage-=10;
            if (indImage >= 0)
            {
                fVideo.set(CAP_PROP_POS_FRAMES, indImage);
                fVideo >> v.x;
            }
            break;
        case 'r':
        {
            fVideo.set(CAP_PROP_POS_FRAMES, 0);
            ofstream fSonde;
            fSonde.open("sonde.txt",ios_base::app);
            if (fSonde.is_open())
            {
                for (int i=0;i<xEnd;i++)
                {
                    fVideo >> v.x;
                    for (int j = 0; j < v.v.size(); j++)
                    {
                        Vec3i w= v.x.at<Vec3b>(v.v[j]);
                        fSonde<<i<< "\t" << v.v[j].x << "\t" << v.v[j].x << "\t" << w[0] << "\t" << w[1] << "\t" << w[2]<<"\n";
                    }

                }
            }

        }


        }

    }

    return 0;
}


void GestionCrayon(int evt, int x, int y, int type, void *extra)
{
    VideoUI *v=(VideoUI*) extra;
    if (type == EVENT_FLAG_LBUTTON)
    {
        v->v.push_back(Point(x/2, y/2));
    }
}

