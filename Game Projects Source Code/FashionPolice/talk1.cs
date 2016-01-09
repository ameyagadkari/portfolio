using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class talk1 : MonoBehaviour {

    public AudioClip sparkle;
    public AudioSource audio;
    movement move;
    [HideInInspector]
    public Quaternion rotation = Quaternion.identity;
    List<GameObject> upperBody;
    List<GameObject> lowerBody;
    //InventoryChanger ic;
    string[] upperBodyItems;
    string[] lowerBodyItems;
    [HideInInspector]
    public bool changeTorso = false;
    [HideInInspector]
    public bool changeLegs = false;
    int dress_indexTorso;
    int dress_indexLegs;
    
    //bool canTalk = true;

    shooter shoot_ref = null;
    InventorySpawnner invent_ref = null;
    movement move_ref = null;
    InventoryChanger invent_change_ref = null;

    //fashion pol ref
    ScoreTracker score_track;

    //Feedback mechanism
    Image speechBubble;
    Text feedback1;
    Text feedback2;
    public GameObject panel;
    float timer;
    public bool clearFeedback = false;

    public enum clothes
    {
        BLOUSE = 0,
        DRESS = 1,
        JACKET = 2,
        MINISKIRT = 3,
        PANTS = 4,
        SHORTS = 5,
        TANKTOP = 6,
        TSHIRT = 7,
        UNLOCKBOOTS = 8,
        UNLOCKVEST = 9,

    };
    public clothes currentCloth;

    void Start()
    {
        timer = 0;
        audio = GetComponent<AudioSource>();
        upperBody = new List<GameObject>();
        lowerBody = new List<GameObject>();
        upperBodyItems = new string[] { "blouse", "jacket", "shirt", "tank" };
        lowerBodyItems = new string[] { "miniskirt", "shorts", "pants", "dress" };

        for (int i = 0; i < 4; i++)
        {
            upperBody.Add(Resources.Load("Prefabs/" + upperBodyItems[i]) as GameObject);
            lowerBody.Add(Resources.Load("Prefabs/" + lowerBodyItems[i]) as GameObject);
        }

        //shooter ref
        shoot_ref = GameObject.Find("Fashion_Shooter_Gun").GetComponent<shooter>();

        //inventory ref
        invent_ref = GameObject.Find("FashionPolice").GetComponent<InventorySpawnner>();

        //movement ref
        move_ref = GameObject.Find("FashionPolice").GetComponent<movement>();

        //inventroy changeref 
        //= GameObject.Find("").GetComponent<InventoryChanger>();

        score_track = GameObject.Find("FashionPolice").GetComponent<ScoreTracker>();
        speechBubble = GameObject.FindGameObjectWithTag("SpeechBubble").GetComponentInChildren<Image>();
        feedback1 = GameObject.Find("SpeechBubble").GetComponentInChildren<Text>();
        feedback2 = GameObject.Find("SpeechBubble").GetComponentInChildren<Text>();
    }

    void OnTriggerEnter(Collider collider)
    {
        //Debug.Log(canTalk);
        if (collider.gameObject.name == "FashionPolice")
        {
            // ic = GameObject.FindGameObjectWithTag("Buttons").GetComponent<InventoryChanger>();
            move = collider.gameObject.GetComponent("movement") as movement;
            move.speed = 0.0f;
            Vector3 player = collider.transform.position;
            player.y = transform.position.y;
            transform.LookAt(player);

            //stop bullet firing until selection            
            shoot_ref.setFire(false);
            move_ref.canMove = false;
            
        }
    }

    public void ActuallyChangeTorso()
    {
        speechBubble.transform.position = new Vector3(panel.transform.position.x, panel.transform.position.y - 200, panel.transform.position.z);
        feedback1.transform.position = new Vector3(panel.transform.position.x + 250, panel.transform.position.y - 150, panel.transform.position.z);

        changeTorso = false;

        score_track.peopleCount++;
        audio.PlayOneShot(sparkle);
        speechBubble.color = Color.white;
        switch (dress_indexTorso)
        {
            case 0:
                if (this.gameObject.name == "Jenni")
                {
                    feedback1.text = "This is fine.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback1.text = "ZOMG I LOVE THIS !!";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback1.text = "I don’t feel comfortable in this.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback1.text = "...";
                }
                feedback1.color = Color.black;
                break;
            case 1:
                if (this.gameObject.name == "Jenni")
                {
                    feedback1.text = "I love this!";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback1.text = "This is so not me.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback1.text = "This is too girly.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback1.text = "This is so banal.";
                }
                feedback1.color = Color.black;
                break;
            case 2:
                if (this.gameObject.name == "Jenni")
                {
                    feedback1.text = "Meh.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback1.text = "Well… OK.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback1.text = "This is too girly.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback1.text = " I hate this.";
                }
                feedback1.color = Color.black;
                break;
            case 3:
                if (this.gameObject.name == "Jenni")
                {
                    feedback1.text = "This is uncomfortable.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback1.text = "Yuck.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback1.text = "Ooooooerz~";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback1.text = " I don’t mind this.";
                }
                feedback1.color = Color.black;
                break;
        }
        Destroy(gameObject.transform.GetChild(1).gameObject);
        score_track.update_score(this.gameObject, (ScoreTracker.clothes)dress_indexTorso);
        GameObject dressUpper = Instantiate(upperBody[dress_indexTorso], transform.position, transform.rotation) as GameObject;
        dressUpper.transform.SetParent(transform);
        dressUpper.transform.SetSiblingIndex(1);
        //isTorsoCovered = true;
        shoot_ref.setFire(false);
        InventoryChanger.isTorsoCovered = true;
        /* if(isTorsoCovered)
         {         
         }*/
    }
    public void ActuallyChangeLegs()
    {
        speechBubble.transform.position = new Vector3(panel.transform.position.x, panel.transform.position.y - 200, panel.transform.position.z);
        feedback1.transform.position = new Vector3(panel.transform.position.x + 250, panel.transform.position.y - 150, panel.transform.position.z);

        changeLegs = false;

        score_track.peopleCount++;
        audio.PlayOneShot(sparkle);
        speechBubble.color = Color.white;
        switch (dress_indexLegs)
        {
            case 0:
                if (this.gameObject.name == "Jenni")
                {
                    feedback2.text = "Ew.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback2.text = "Well… OK.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback2.text = "This is so fetch.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback2.text = "Not feeling this one.";
                }
                feedback2.color = Color.black;
                break;
            case 1:
                if (this.gameObject.name == "Jenni")
                {
                    feedback2.text = "This is ugly.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback2.text = "So. Bland.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback2.text = "Eh… whatever, then.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback2.text = "OH MAN! ";
                }
                feedback2.color = Color.black;
                break;
            case 2:
                if (this.gameObject.name == "Jenni")
                {
                    feedback2.text = "What a perfect fit!";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback2.text = "Yuck.";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback2.text = "This is too girly.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback2.text = "Uh… no.";
                }
                feedback2.color = Color.black;
                break;
            case 3:
                if (this.gameObject.name == "Jenni")
                {
                    feedback2.text = "This is OK, but not really my style.";
                }
                if (this.gameObject.name == "Andrew")
                {
                    feedback2.text = "ZOMG I LOVE THIS !!";
                }
                if (this.gameObject.name == "Melissa")
                {
                    feedback2.text = "As if.";
                }
                if (this.gameObject.name == "Julian")
                {
                    feedback2.text = "Uh… no.";
                }
                feedback2.color = Color.black;
                break;
        }

        Destroy(gameObject.transform.GetChild(0).gameObject);
        score_track.update_score(this.gameObject, (ScoreTracker.clothes)dress_indexLegs);
        GameObject dressUpper = Instantiate(lowerBody[dress_indexLegs], transform.position, transform.rotation) as GameObject;
        dressUpper.transform.SetParent(transform);
        dressUpper.transform.SetSiblingIndex(0);
        invent_ref.clearDisplay();
        move_ref.canMove = true;
        GetComponent<Collider>().enabled = false;
        InventoryChanger.isTorsoCovered = false;

        removeText();
        clearFeedback = true;
        //isTorsoCovered = false;

    }

    void removeText()
    {
        timer = 0;
    }

    void Update()
    {
        
        timer += Time.deltaTime;
        Debug.Log(timer);
        if (timer >= 1 && (clearFeedback))
        {
            speechBubble.color = Color.clear;
            feedback1.text = "";
            feedback2.text = "";
            clearFeedback = false;
        }
    }

    public void ChangeTorso(int dressSelect)
    {
        changeTorso = true;
        dress_indexTorso = dressSelect;
        //if (isTorsoCovered)
        //{
            shoot_ref.setFire(true);
        //}

    }
    public void ChangeLegs(int dressSelect)
    {
        changeLegs = true;
        dress_indexLegs = dressSelect;
        shoot_ref.setFire(true);
    }
}

