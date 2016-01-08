using UnityEngine;
using System.Collections;

public class BordSelector : MonoBehaviour
{

    MainScript mainScript;

    // Use this for initialization
    void Start()
    {
        mainScript = GameObject.Find("Script Loader").GetComponent<MainScript>();
    }

    // Update is called once per frame
    public void UpdColor(int color_int)
    {
        if(gameObject.transform.parent.name == "Color Border(Clone)")            
            mainScript.setBackColor(color_int);
        else
            mainScript.setFillColor(color_int);
    }
}
