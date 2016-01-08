using UnityEngine;
using System.Collections;

public class PatternSelector : MonoBehaviour {
    MainScript mainScript;
    void Start()
    {
        mainScript = GameObject.Find("Script Loader").GetComponent<MainScript>();
    }
    public void SelectPattern(int patternNumber)
    {
        //Debug.Log(patternNumber);
        mainScript.SelectPattern(patternNumber);
    }  
}
