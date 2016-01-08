using UnityEngine;
using System.Collections;

public class Refresh : MonoBehaviour {
    MainScript mainScript;
    void Start()
    {
        mainScript = GameObject.Find("Script Loader").GetComponent<MainScript>();
    }
    public void RefreshScreen()
    {
        mainScript.RefreshScreen();
    }
}
