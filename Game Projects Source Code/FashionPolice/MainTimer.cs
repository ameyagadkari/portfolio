using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System.Collections.Generic;

public class MainTimer : MonoBehaviour
{
    public Text timerLabel;
    public Texture highScoreMenu;
    public GameObject panel;

    private float time;
    float minutes;
    float seconds;
    float fraction;
    bool stopTimer;
    bool displayScore;
    Image highScoreMenuScript;
    Text finalScoreScript;
    ScoreTracker score_track;
    public GameObject[] buttonReferences;
    [HideInInspector]
    public List<GameObject> buttons;

    void Start()
    {
        highScoreMenuScript = GameObject.Find("HighScoreMenu").GetComponent<Image>();
        finalScoreScript = GameObject.Find("HighScoreMenu").GetComponentInChildren<Text>();
        score_track = GameObject.Find("FashionPolice").GetComponent<ScoreTracker>();
        stopTimer = false;
        displayScore = false;
    }

    void Update()
    {
        time += Time.deltaTime;

        if (!stopTimer)
        {
            minutes = time / 60;  
            seconds = time % 60; 
            fraction = (time * 100) % 100;

           // Debug.Log("minutes->"+ minutes+"  seconds->"+seconds+"  fraction->"+fraction);
            
            timerLabel.text = string.Format("{0:0} : {1:00} : {2:000}", minutes/2, seconds, fraction);
            
            if (minutes >=0.99f || score_track.peopleCount >= 8)
            {
                stopTimer = true;
                Time.timeScale = 0.0f;
                timerLabel.text = "TIME UP !";
                displayScore = true;

                highScoreMenuScript.color = Color.white;
                finalScoreScript.color = Color.white;
                finalScoreScript.text = score_track.player_score.ToString();
                SpawnButtons();
            }
        }
    }

    void SpawnButtons()
    {
        //for Restart Button
        GameObject button0 = Instantiate(buttonReferences[0] as GameObject);
        button0.transform.SetParent(panel.transform);
        button0.transform.position = new Vector3(panel.transform.position.x - 100, panel.transform.position.y - 137, panel.transform.position.z);
        button0.transform.localScale = new Vector3(1, 2, 2);
        button0.transform.rotation = panel.transform.rotation;
        buttons.Add(button0);

        //for Exit Button
        GameObject button1 = Instantiate(buttonReferences[1] as GameObject);
        button1.transform.SetParent(panel.transform);
        button1.transform.position = new Vector3(panel.transform.position.x + 85, panel.transform.position.y - 137, panel.transform.position.z);
        button1.transform.localScale = new Vector3(1, 2, 2);
        button1.transform.rotation = panel.transform.rotation;
        buttons.Add(button1);
    }
}