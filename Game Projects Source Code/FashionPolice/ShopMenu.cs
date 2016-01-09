using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class ShopMenu : MonoBehaviour {
    public GameObject[] buttonReferences;
    List<GameObject> buttons;
    public GameObject shopPanel;
    Image shopPanelImageScript;
    bool isdisplayed;
    void Start()
    {
        buttons = new List<GameObject>();
        shopPanelImageScript = shopPanel.GetComponent<Image>();
        isdisplayed = false;
    }
    public void SpawnDestroyButtons()
    {
        if(!isdisplayed)
        {
            Time.timeScale = 0;
            isdisplayed = true;
            shopPanelImageScript.color = Color.white;
            SpawnButtons();
        }
        else
        {
            Time.timeScale = 1;
            isdisplayed = false;
            shopPanelImageScript.color = Color.clear;
            DestroyButtons();
        }
    }
    void SpawnButtons()
    {
        int offset = 1;
        for (int i = 0; i < buttonReferences.Length; i++)
        {
            GameObject button = Instantiate(buttonReferences[i] as GameObject);
            button.transform.SetParent(shopPanel.transform);
            button.transform.position = shopPanel.transform.position - new Vector3(offset-- * 400, 300, 0);
            button.transform.localScale = Vector3.one;
            button.transform.rotation = shopPanel.transform.rotation;
            buttons.Add(button);
        }
    }
    void DestroyButtons()
    {
        for (int i = 0; i < buttons.Count; i++)
        {
            Destroy(buttons[i]);
        }
        buttons.Clear();
    }
}
