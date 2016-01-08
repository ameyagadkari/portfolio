using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class BackgroundSelector : MonoBehaviour {
    public Sprite[] backgrounds;
    Image imageScript;
    static int backgroundSelector;
    void Start()
    {
        backgroundSelector = 0;
        imageScript = GameObject.FindGameObjectWithTag("MainGameBackgound").GetComponent<Image>();
    }
    public void ChangeBackground()
    {
        if (backgroundSelector == 9)
        {
            backgroundSelector = 0;
        }
        else
        {
            backgroundSelector++;
        }
        imageScript.sprite = backgrounds[backgroundSelector];
    }
}
