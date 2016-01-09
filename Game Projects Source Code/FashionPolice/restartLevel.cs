using UnityEngine;
using System.Collections;

public class restartLevel : MonoBehaviour {

	public void restartNow()
    {
        Application.LoadLevel("FashionPolice");
        Time.timeScale = 1.0f;
    }
}
