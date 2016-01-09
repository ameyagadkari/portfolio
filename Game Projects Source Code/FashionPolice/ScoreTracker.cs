using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ScoreTracker : MonoBehaviour
{
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
    Text currentScoreScript;

    // Use this for initialization
    public int player_score = 0;
    public int peopleCount;

    void Start()
    {
        currentScoreScript = GameObject.Find("CurrentScore").GetComponent<Text>();
        peopleCount = 0;
    }

    // Update is called once per frame
    void Update()
    {
        currentScoreScript.text = "SCORE : " + player_score;
    }

    public int update_score(GameObject npc, clothes cloth)
    {
        int ret_value = 0;
        switch (npc.name)
        {
            case "Jenni":
                switch (cloth)
                {
                    case clothes.BLOUSE:
                        ret_value = 4;
                        break;
                    case clothes.DRESS:
                        ret_value = 4;
                        break;
                    case clothes.JACKET:
                        ret_value = 5;
                        break;
                    case clothes.MINISKIRT:
                        ret_value = 2;
                        break;
                    case clothes.PANTS:
                        ret_value = 5;
                        break;
                    case clothes.SHORTS:
                        ret_value = 2;
                        break;
                    case clothes.TANKTOP:
                        ret_value = 3;
                        break;
                    case clothes.TSHIRT:
                        ret_value = 3;
                        break;
                    case clothes.UNLOCKBOOTS:
                        ret_value = 5;
                        break;
                    case clothes.UNLOCKVEST:
                        ret_value = 5;
                        break;
                    default:
                        ret_value = 1;
                        break;
                }
                break;

            case "Andrew":
                switch (cloth)
                {
                    case clothes.BLOUSE:
                        ret_value = 5;
                        break;
                    case clothes.DRESS:
                        ret_value = 5;
                        break;
                    case clothes.JACKET:
                        ret_value = 3;
                        break;
                    case clothes.MINISKIRT:
                        ret_value = 4;
                        break;
                    case clothes.PANTS:
                        ret_value = 3;
                        break;
                    case clothes.SHORTS:
                        ret_value = 4;
                        break;
                    case clothes.TANKTOP:
                        ret_value = 2;
                        break;
                    case clothes.TSHIRT:
                        ret_value = 2;
                        break;
                    case clothes.UNLOCKBOOTS:
                        ret_value = 5;
                        break;
                    case clothes.UNLOCKVEST:
                        ret_value = 5;
                        break;
                    default:
                        ret_value = 1;
                        break;
                }
                break;

            case "Melissa":
                switch (cloth)
                {
                    case clothes.BLOUSE:
                        ret_value = 2;
                        break;
                    case clothes.DRESS:
                        ret_value = 2;
                        break;
                    case clothes.JACKET:
                        ret_value = 3;
                        break;
                    case clothes.MINISKIRT:
                        ret_value = 5;
                        break;
                    case clothes.PANTS:
                        ret_value = 3;
                        break;
                    case clothes.SHORTS:
                        ret_value = 4;
                        break;
                    case clothes.TANKTOP:
                        ret_value = 5;
                        break;
                    case clothes.TSHIRT:
                        ret_value = 4;
                        break;
                    case clothes.UNLOCKBOOTS:
                        ret_value = 5;
                        break;
                    case clothes.UNLOCKVEST:
                        ret_value = 5;
                        break;
                    default:
                        ret_value = 1;
                        break;
                }
                break;

            case "Julian":
                switch (cloth)
                {
                    case clothes.BLOUSE:
                        ret_value = 2;
                        break;
                    case clothes.DRESS:
                        ret_value = 2;
                        break;
                    case clothes.JACKET:
                        ret_value = 3;
                        break;
                    case clothes.MINISKIRT:
                        ret_value = 5;
                        break;
                    case clothes.PANTS:
                        ret_value = 3;
                        break;
                    case clothes.SHORTS:
                        ret_value = 4;
                        break;
                    case clothes.TANKTOP:
                        ret_value = 5;
                        break;
                    case clothes.TSHIRT:
                        ret_value = 4;
                        break;
                    case clothes.UNLOCKBOOTS:
                        ret_value = 5;
                        break;
                    case clothes.UNLOCKVEST:
                        ret_value = 5;
                        break;
                    default:
                        ret_value = 1;
                        break;
                }
                break;
        }

        player_score += ret_value;
        return ret_value;
    }
}
