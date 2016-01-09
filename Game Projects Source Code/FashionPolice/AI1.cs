using UnityEngine;
using System.Collections;

public class AI1 : MonoBehaviour {

    float timer;
    bool beginMoving;

	void Start () {
        timer = 0.0f;
        beginMoving = true;
    }
	
	void Update () {
        timer += Time.deltaTime * 3;

        if (timer > 25)
            timer = 0.0f;

      //  Debug.Log(timer);
        if(beginMoving)
        {
            if (timer < 5 && timer > 0)
                //transform.Rotate(0, 90, 0);
                transform.position += Vector3.forward * Time.deltaTime;
            else if (timer > 5 && timer < 10)
                transform.position += Vector3.left * Time.deltaTime;
            else if (timer > 10 && timer < 15)
                transform.position += Vector3.right * Time.deltaTime;
            else if (timer > 15 && timer < 25)
                transform.position += Vector3.back * Time.deltaTime;
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "FashionPolice")
        {
            beginMoving = false;
        }
    }
    void OnTriggerExit(Collider collider)
    {
        if (collider.gameObject.name == "FashionPolice")
        {
            beginMoving = true;
        }
    }
}
