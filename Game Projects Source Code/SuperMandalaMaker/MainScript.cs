using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class MainScript : MonoBehaviour {
    public class PatternList
    {
        public float radius;
        public float size;
        public int quantity;
        public float orientation;
        public float alignment;
        public int patternNumber;
        //public Texture2D pattern;
        public Texture2D mainTexture;
        public Texture2D refTexture;
        public Color borderColor;
        public Color insideColor;
        public bool isFinal;
        RectTransform canvasRectTransform;        

        public PatternList(float radius, float size, int quantity, int patternNumber, Texture2D i_refTexture, Color borderColor, Color insideColor)
        {
            canvasRectTransform = GameObject.Find("Canvas").GetComponent<RectTransform>();
            this.radius = radius;
            this.size = size;
            this.quantity = quantity;
            this.patternNumber = patternNumber;
            refTexture = Texture2D.Instantiate(i_refTexture);
            mainTexture = Texture2D.Instantiate(refTexture);
            this.borderColor = borderColor;
            this.insideColor = insideColor;
            isFinal = false;
        }

        void Start()
        {
            orientation = 0.0f;
            alignment = 0.0f;
        }
        

        public void DrawCircularPattern()
        {
            float degrees = 0.0f;
            for (int i = 0; i < quantity; i++)
            {
                Matrix4x4 matrixBackup = GUI.matrix;
                GUIUtility.RotateAroundPivot(degrees + 98 + orientation, new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + canvasRectTransform.position.x, radius * Mathf.Sin(degrees * Mathf.PI / 180) + Screen.height / 2));
                Rect r2 = new Rect(new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + Screen.width / 2, radius * Mathf.Sin(degrees * Mathf.PI / 180) + canvasRectTransform.position.y), new Vector2(size, size));
                GUI.DrawTexture(r2, mainTexture);
                degrees += (18.0f + alignment);
                GUI.matrix = matrixBackup;

            }
        }


        public void AnimatePattern(float degrees)
        {
            
            for (int i = 0; i < quantity; i++)
            {
                Matrix4x4 matrixBackup = GUI.matrix;
                GUIUtility.RotateAroundPivot(degrees + 98 + orientation, new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + canvasRectTransform.position.x, radius * Mathf.Sin(degrees * Mathf.PI / 180) + Screen.height / 2));
                Rect r2 = new Rect(new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + Screen.width / 2, radius * Mathf.Sin(degrees * Mathf.PI / 180) + canvasRectTransform.position.y), new Vector2(size, size));
                GUI.DrawTexture(r2, mainTexture);
                degrees += (18.0f + alignment);
                GUI.matrix = matrixBackup;

            }
        }

        public void AnimateCounterPattern(float degrees)
        {

            for (int i = 0; i < quantity; i++)
            {
                Matrix4x4 matrixBackup = GUI.matrix;
                GUIUtility.RotateAroundPivot(degrees + 98 + orientation, new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + canvasRectTransform.position.x, radius * Mathf.Sin(degrees * Mathf.PI / 180) + Screen.height / 2));
                Rect r2 = new Rect(new Vector2(radius * Mathf.Cos(degrees * Mathf.PI / 180) + Screen.width / 2, radius * Mathf.Sin(degrees * Mathf.PI / 180) + canvasRectTransform.position.y), new Vector2(size, size));
                GUI.DrawTexture(r2, mainTexture);
                degrees -= (18.0f + alignment);
                GUI.matrix = matrixBackup;

            }
        }

        public void SetRadius(float radius)
        {
            this.radius = radius;
        }
        public void SetSize(float size)
        {
            this.size = size;
        }
        public void SetQuantity(float quantity)
        {
            this.quantity = (int)quantity;
        }
        public void setOrientation(float newOrientation)
        {
            orientation = newOrientation;
        }
        
        public Texture2D getMainTexture()
        {
            return mainTexture;
        }

        public Texture2D getRefTexture()
        {
            return refTexture;
        }

        public void setMainTexture(Texture2D tex)
        {
            mainTexture = tex; ;
        }

        public Color getBorderColor()
        {
            return borderColor;
        }

        public Color getInsideColor()
        {
            return insideColor;
        }
        public float getOrientation()
        {
            return orientation;
        }
    }

    //public Texture2D[] presetPieces;
    public Texture2D[] patterns;
    public Texture2D[] patterns_backup;

    // Color coding
    Color foreGroundColor;
    Color BackGroundColor;
    Image imageScript;

    List<PatternList> patternList;

    int layerNumber;
    int patternNumber;

    float radius;
    float size;
    int quantity;

    bool isBaking;
    bool differentPatternSelected;
    bool isCurrentPatternSelected;
    //Rotation Feature
    public float orientation;
    //Alignment Feature
    public float alignment;
    public bool isAnimate;
    public float timer = 0.0f;
    public float timer_max = 3.0f;
    public float ani_degs = 0;
    public float ani_ctr_degs = 0;

    //Scratching feature
    public bool changeColor;
    public Texture2D redBar;
    public Texture2D greenBar;
    float increment;
    bool triggerColorChange;
    Color newColor;

    void Start()
    {
        patternList = new List<PatternList>();

        radius = 400f;
        size = 100f;
        quantity = 21;

        layerNumber = -1;
        patternNumber = 0;

        isBaking = false;
        differentPatternSelected = false;
        isCurrentPatternSelected = true;
        imageScript = gameObject.GetComponent<Image>();
        changeColor = false;
        triggerColorChange = false;
    }
    public void SelectPattern(int patternNumber)
    {
        this.patternNumber = patternNumber;
        if (!isBaking && (patternList.Count - 1 == layerNumber))
        {
            patternList.Add(new PatternList(radius, size, quantity, this.patternNumber, patterns_backup[this.patternNumber], Color.red, Color.blue));
            layerNumber++;
            isBaking = true;
        }
        differentPatternSelected = true;
    }
    public void BakeLayer()
    {
        isBaking = false;
        if (layerNumber > -1 && isCurrentPatternSelected)
        {
            patternList[layerNumber].isFinal = true;
        } 
    }

    public void GoToNextPattern()
    {
        if (layerNumber < patternList.Count - 1)
        {
            isBaking = false;
            patternList[layerNumber].isFinal = true;
            layerNumber++;
            patternList[layerNumber].isFinal = false;
            if (layerNumber == patternList.Count - 1)
            {
                isCurrentPatternSelected = true;
            }
            else
            {
                isCurrentPatternSelected = false;
            }
        }
    }

    public void GoToPreviousPattern()
    {
        if(layerNumber>0)
        {
            isBaking = false;
            patternList[layerNumber].isFinal = true;
            layerNumber--;
            patternList[layerNumber].isFinal = false;
            if (layerNumber == patternList.Count - 1)
            {
                isCurrentPatternSelected = true;
            }
            else
            {
                isCurrentPatternSelected = false;
            } 
        }
    }
    public void ChangeRadius(float radius)
    {
        this.radius = radius;
        if (layerNumber > -1)
        {
            if(!patternList[layerNumber].isFinal)
            {
                patternList[layerNumber].radius = this.radius;
            }     
        }
    }
    public void ChangeSize(float size)
    {
        this.size = size;
        if (layerNumber > -1)
        {
            if (!patternList[layerNumber].isFinal)
            {
                patternList[layerNumber].size = this.size;
            }
        }
    }
    public void ChangeQuantity(float quantity)
    {
        this.quantity = (int)quantity;
        if (layerNumber > -1)
        {
            if (!patternList[layerNumber].isFinal)
            {
                patternList[layerNumber].quantity = this.quantity;
            }
        }
    }
    public void ChangeOrientation(float newOrientation)
    {
        orientation = newOrientation;
        patternList[layerNumber].orientation = orientation;
    }

    public void ChangeAlignment(float newAlignment)
    {
        alignment = newAlignment;
        patternList[layerNumber].alignment = alignment;
    }
    public void RefreshScreen()
    {
        patternList.Clear();
        layerNumber = -1;
        patternNumber = 0;

        isBaking = false;
        differentPatternSelected = false;
        isCurrentPatternSelected = true;
    }

    


    public bool setBorderColor(Texture2D change_tex, Texture2D ref_tex, Color color)
    {
        for (int y = 0; y < change_tex.height; y++)
            for (int x = 0; x < change_tex.width; x++)
            {
                //if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r == Color.white.r && ref_tex.GetPixel(x, y).g == Color.white.g && ref_tex.GetPixel(x, y).g == Color.white.g)
                //    if (change_tex.GetPixel(x, y).r == color.r && change_tex.GetPixel(x, y).g == color.g && change_tex.GetPixel(x, y).g == color.g)
                //        return false;

                //if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r == Color.black.r && ref_tex.GetPixel(x, y).g == Color.black.g && ref_tex.GetPixel(x, y).g == Color.black.g)
                //    if (change_tex.GetPixel(x, y).r == color.r && change_tex.GetPixel(x, y).g == color.g && change_tex.GetPixel(x, y).g == color.g)
                //        return true;

                if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r != Color.white.r && ref_tex.GetPixel(x, y).b != Color.white.b && ref_tex.GetPixel(x, y).g != Color.white.g)
                {
                    //Debug.Log("Detec");
                    //Debug.Log(ref_tex.GetPixel(x, y).r);
                    //Debug.Log(ref_tex.GetPixel(x, y).b);
                    //Debug.Log(ref_tex.GetPixel(x, y).g);
                    change_tex.SetPixel(x, y, color);
                }    
            }

        change_tex.Apply();
        // count_debug++;
        // Debug.Log(count_debug);
        return true;
    }

    public bool setInsideColor(Texture2D change_tex, Texture2D ref_tex, Color color)
    {
        for (int y = 0; y < change_tex.height; y++)
            for (int x = 0; x < change_tex.width; x++)
            {
                if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r == Color.black.r && ref_tex.GetPixel(x, y).g == Color.black.g && ref_tex.GetPixel(x, y).g == Color.black.g)
                    if (change_tex.GetPixel(x, y).r == color.r && change_tex.GetPixel(x, y).g == color.g && change_tex.GetPixel(x, y).g == color.g)
                        return false;

                if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r == Color.white.r && ref_tex.GetPixel(x, y).g == Color.white.g && ref_tex.GetPixel(x, y).g == Color.white.g)
                    if (change_tex.GetPixel(x, y).r == color.r && change_tex.GetPixel(x, y).g == color.g && change_tex.GetPixel(x, y).g == color.g)
                        return true;

                if (change_tex.GetPixel(x, y).a != 0 && ref_tex.GetPixel(x, y).r == Color.white.r && ref_tex.GetPixel(x, y).g == Color.white.g && ref_tex.GetPixel(x, y).g == Color.white.g)
                    change_tex.SetPixel(x, y, color);
            }

        change_tex.Apply();
        return true;
    }


    public void Animate()
    {
        if (isAnimate)
            isAnimate = false;
        else
            isAnimate = true;

    }

    void OnGUI()
    {
        GUI.DrawTexture(new Rect(Screen.width - 50, Screen.height - 470, 45, 320), redBar);

        if (Input.GetMouseButton(0)&&changeColor)
        {
            increment += Time.deltaTime * 50;
            if (increment <= 320)
            {
                GUI.DrawTexture(new Rect(Screen.width - 50, Screen.height - 470, 45, increment), greenBar);
                if (increment > 319)
                {
                    triggerColorChange = true;
                }
            }
        }

        if (triggerColorChange)
        {
            changeColor = false;
            triggerColorChange = false;
            increment = 0;
            Texture2D temp_main_tex = patternList[layerNumber].getMainTexture();
            Texture2D temp_ref_tex = patternList[layerNumber].getRefTexture();
            //patternList[layerNumber].insideColor = newColor;
            if (setInsideColor(temp_main_tex, temp_ref_tex, newColor) == true)
            {
                Debug.Log(layerNumber);
                patternList[layerNumber].setMainTexture(temp_main_tex);
            }
        }

        if (!isAnimate)
        {
            if (differentPatternSelected && (layerNumber > -1))
            {
                if (!patternList[layerNumber].isFinal)
                {
                    patternList[layerNumber].refTexture = patterns_backup[patternNumber];
                }
                differentPatternSelected = false;
            }

            for (int i = 0; i < patternList.Count; i++)
            {
                //Texture2D temp_main_tex = patternList[i].getMainTexture();
                //Texture2D temp_ref_tex = patternList[i].getRefTexture();
                //Color border = patternList[i].getBorderColor();
                //Color inside = patternList[i].getInsideColor();
                //if (setBorderColor(temp_main_tex, temp_ref_tex, border) == true && setInsideColor(temp_main_tex, temp_ref_tex, inside) == true)
                //{
                patternList[i].DrawCircularPattern();
                //Debug.Log(true);
                //}
                //else
                //    Debug.Log(false);
            }
        }
        else
        {
            for (int i = 0; i < patternList.Count; i++)
            {
                //Texture2D temp_main_tex = patternList[i].getMainTexture();
                //Texture2D temp_ref_tex = patternList[i].getRefTexture();
                //Color border = patternList[i].getBorderColor();
                //Color inside = patternList[i].getInsideColor();
                //if (setBorderColor(temp_main_tex, temp_ref_tex, border) == true && setInsideColor(temp_main_tex, temp_ref_tex, inside) == true)
                //{
                if (i % 2 == 0)                
                    patternList[i].AnimatePattern(ani_degs);
                else
                    patternList[i].AnimateCounterPattern(ani_ctr_degs);

                //Debug.Log(true);
                //}
                //else
                //    Debug.Log(false);
            }
            ani_degs += 0.3f;
            ani_ctr_degs -= 0.3f;

        }
        



    }


    public void setBackColor(int color_int)
    {
        Debug.Log("back");
        Texture2D temp_main_tex = patternList[layerNumber].getMainTexture();
        Texture2D temp_ref_tex = patternList[layerNumber].getRefTexture();
        //Color border = patternList[i].getBorderColor();
        //Color inside = patternList[i].getInsideColor();
        Color temp_color = Color.black; 


        switch (color_int)
        {
            case 0:
                temp_color = Color.black;
                break;
            case 1:
                temp_color = Color.blue;
                break;
            case 2:
                temp_color = new Color(0.32f,0.16f,0,1);
                break;
            case 3:
                temp_color = new Color(0,0.39f,0.06f,1);
                break;
            case 4:
                temp_color = new Color(0.26f, 0.26f, 0.26f,1);
                break;
            case 5:
                temp_color = new Color(0.09f,0.71f,0.06f,1);
                break;
            case 6:
                temp_color = new Color(0.52f, 0.52f, 0.52f,1);
                break;
            case 7:
                temp_color = new Color(0,0.68f,0.93f,1);
                break;
            case 8:
                temp_color = new Color(0.59f,0.45f,0.22f,1);
                break;
            case 9:
                temp_color = new Color(0.77f, 0.77f, 0.77f,1);
                break;
            case 10:
                temp_color = new Color(0.96f, 0.03f, 0.52f, 1);
                break;
            case 11:
                temp_color = new Color(1,0.39f,0,1);
                break;
            case 12:
                temp_color = new Color(0.26f, 0, 0.64f, 1);
                break;
            case 13:
                temp_color = new Color(0.87f,0.03f,0,1);
                break;
            case 14:
                temp_color = Color.white;
                break;
            case 15:
                temp_color = Color.yellow;
                break;
        }



        Debug.Log(layerNumber);
        if (setBorderColor(temp_main_tex, temp_ref_tex, temp_color) == true)
        {
            Debug.Log(layerNumber);
            patternList[layerNumber].setMainTexture(temp_main_tex);

        }

    }



    public void setFillColor(int color_int)
    {
        Texture2D temp_main_tex = patternList[layerNumber].getMainTexture();
        Texture2D temp_ref_tex = patternList[layerNumber].getRefTexture();
        //Color border = patternList[i].getBorderColor();
        //Color inside = patternList[i].getInsideColor();
        Color temp_color = Color.black;


        switch (color_int)
        {
            case 0:
                temp_color = Color.black;
                break;
            case 1:
                temp_color = Color.blue;
                break;
            case 2:
                temp_color = new Color(0.32f, 0.16f, 0, 1);
                break;
            case 3:
                temp_color = new Color(0, 0.39f, 0.06f, 1);
                break;
            case 4:
                temp_color = new Color(0.26f, 0.26f, 0.26f, 1);
                break;
            case 5:
                temp_color = new Color(0.09f, 0.71f, 0.06f, 1);
                break;
            case 6:
                temp_color = new Color(0.52f, 0.52f, 0.52f, 1);
                break;
            case 7:
                temp_color = new Color(0, 0.68f, 0.93f, 1);
                break;
            case 8:
                temp_color = new Color(0.59f, 0.45f, 0.22f, 1);
                break;
            case 9:
                temp_color = new Color(0.77f, 0.77f, 0.77f, 1);
                break;
            case 10:
                temp_color = new Color(0.96f, 0.03f, 0.52f, 1);
                break;
            case 11:
                temp_color = new Color(1, 0.39f, 0, 1);
                break;
            case 12:
                temp_color = new Color(0.26f, 0, 0.64f, 1);
                break;
            case 13:
                temp_color = new Color(0.87f, 0.03f, 0, 1);
                break;
            case 14:
                temp_color = Color.white;
                break;
            case 15:
                temp_color = Color.yellow;
                break;
        }

        changeColor = true;
        newColor = temp_color;

        Debug.Log(layerNumber);
      /*  if (setInsideColor(temp_main_tex, temp_ref_tex, temp_color) == true)
        {
            Debug.Log(layerNumber);
            //patternList[layerNumber].setMainTexture(temp_main_tex);

        }*/

    }


}
