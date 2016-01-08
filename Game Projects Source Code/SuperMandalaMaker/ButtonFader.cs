using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ButtonFader : MonoBehaviour {
    public bool faded = false;

    Image buttonImage;
    Text buttonText;
    Color buttonColor;
    Color textColor;
    bool startFade = false;
    float smooth = 0;
    bool initialized = false;

    void Start()
    {
        Initialize();
    }
    void Initialize()
    {
        startFade = false;
        faded = false;
        buttonImage = GetComponent<Image>();
        buttonColor = buttonImage.color;
        if(GetComponentInChildren<Text>())
        {
            buttonText = GetComponent<Text>();
            textColor = buttonText.color;
        }
        initialized = true;
    }
    void Update()
    {
        if(startFade)
        {
            Fade(smooth);
            if (buttonColor.a > 0.9)
            {
                faded = true;
            }
        }
    }
    public void Fade(float smooth)
    {
        if(!initialized)
        {
            Initialize();
        }
        this.smooth = smooth;
        startFade = true;
        buttonColor.a += smooth;
        buttonImage.color = buttonColor;
        if(buttonText)
        {
            textColor.a += smooth;
            buttonText.color = textColor;
        }
    }
}
