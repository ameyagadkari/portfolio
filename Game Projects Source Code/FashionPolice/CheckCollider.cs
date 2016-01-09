using UnityEngine;
using System.Collections;

public class CheckCollider : MonoBehaviour {
    talk1 talk1Script;
    void Start()
    {
        talk1Script = GetComponentInParent<talk1>();
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.name == "glamBullet(Clone)" && gameObject.name== "GNM-Top" && talk1Script.changeTorso == true)
        {
            talk1Script.ActuallyChangeTorso();
        }
        if (collision.collider.name == "glamBullet(Clone)" && gameObject.name == "GNM-Bottom" && talk1Script.changeLegs == true)
        {
            talk1Script.ActuallyChangeLegs();
        }
    }
}
